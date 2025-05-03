//
// Created by 10580.
//

#ifndef TSINGHUA_DSA_INCLUDE_DSA_HASHTABLE_HPP
#define TSINGHUA_DSA_INCLUDE_DSA_HASHTABLE_HPP
#include <iostream>
#include <type_traits>
#include <vector>
#include "allocator.hpp"

namespace ds {
template<typename Value>
struct htnode
{
    htnode *next;
    Value value;
};

template<typename Value, typename Key, typename HashFn, typename ExtractKey>
class hash_table;
template<typename Value, typename Key, typename HashFn, typename ExtractKey>
class ht_iterator
{
public:
    using value_type        = Value;
    using pointer           = value_type *;
    using reference         = value_type &;
    using iterator_category = std::forward_iterator_tag;
    using iterator          = ht_iterator;
    using difference_type   = std::ptrdiff_t;

private:
    using node = htnode<Value>;
    using ht   = hash_table<Value, Key, HashFn, ExtractKey>;

    node *m_cur;
    const ht *m_ht;

public:
    ht_iterator(node *pnode, const ht *pht) : m_cur(pnode), m_ht(pht) {}
    reference operator*() const noexcept
    {
        return m_cur->value;
    }
    pointer operator->() const noexcept
    {
        return &operator*();
    }
    bool operator==(const iterator &other) const noexcept
    {
        return m_cur == other.m_cur;
    }
    bool operator!=(const iterator &other) const noexcept
    {
        return !(*this == other);
    }
    iterator &operator++() noexcept
    {
        node *old = m_cur;
        m_cur = m_cur->next;
        if (!m_cur) {
            size_t idx = m_ht->get_bucket_index(old->value);
            while (!m_cur && ++idx < m_ht->m_buckets.size()) {
                m_cur = m_ht->m_buckets[idx];
            }
        }
        return *this;
    }

};

template<typename Value, typename Key, typename HashFn, typename ExtractKey>
class hash_table
{
public:
    using value_type        = Value;
    using key_type          = Key;
    using iterator          = ht_iterator<Value, Key, HashFn, ExtractKey>;
    using difference_type   = std::ptrdiff_t;

    using node              = htnode<Value>;
    friend iterator ;

private:
    HashFn m_hash;
    ExtractKey m_getkey;
    std::vector<node *> m_buckets;
    size_t m_size;

    static constexpr int N = 28;
    inline static constexpr unsigned long primes_list[N] {
            53ul, 97ul, 193ul, 389ul, 769ul,
            1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
            49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
            1572869ul, 3145739ul, 6291469ul, 25165843ul, 12582917ul,
            50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
            1610612741ul, 3221225473ul,4294967291ul
    };
    static constexpr unsigned long _next_prime(unsigned long n) noexcept
    {
        const unsigned long *first = primes_list;
        const unsigned long *last = primes_list + N;
        const unsigned long *pos = std::lower_bound(first, last, n);
        return pos == last ? *(last - 1) : *pos;
    }
    [[nodiscard]]
    size_t next_prime(size_t n) const noexcept
    {
        return _next_prime(n);
    }
    size_t get_bucket_index(const value_type &value) const
    {
        return m_hash(m_getkey(value)) % m_buckets.size();
    }
    size_t get_bucket_index(const value_type &value, size_t bucketsize) const
    {
        return m_hash(m_getkey(value)) % bucketsize;
    }
    [[nodiscard]]
    constexpr double max_load_factor() const
    {
        return 1;
    }
    void rehash(size_t newsize_hint)
    {
        size_t nbuckets = next_prime(newsize_hint);
        while (1.0 * m_size / (1.0 * m_buckets.size()) > max_load_factor()) {
            nbuckets = next_prime(nbuckets + 1);
        }
        std::vector<node *> newbuckets(nbuckets);
        for (auto &head : m_buckets) {
            while (head != nullptr) {
                node *cur = head;
                size_t idx = get_bucket_index(cur->value, nbuckets);
                head = cur->next;

                cur->next = newbuckets[idx];
                newbuckets[idx] = cur;
            }
        }
        std::swap(m_buckets, newbuckets);
    }
    static node *alloc_node()
    {
        node *newnode = ds::allocator<node>::allocate();
        newnode->next = nullptr;
        return newnode;
    }
    static void dealloc_node(node *pnode)
    {
        return ds::allocator<node>::deallocate(pnode);
    }


public:
    explicit hash_table(size_t bucketsize_hint = 1,
               const HashFn &fn = HashFn{},
               const ExtractKey &getkey = ExtractKey{}) noexcept
               : m_hash(fn), m_getkey(getkey), m_size(0)
    {
        const size_t nbuckets = next_prime(bucketsize_hint);
        m_buckets.assign(nbuckets, nullptr);
    }
    iterator insert(const value_type &value)
    {
        if (1.0 * (m_size + 1) / (1.0 * m_buckets.size()) > max_load_factor()) {
            rehash(m_buckets.size() + 1);
        }
        auto it = find(value);
        if (it != end()) {
            return it;
        }
        size_t idx = get_bucket_index(value);
        node *newnode = alloc_node();
        std::construct_at(&newnode->value);
        newnode->next = m_buckets[idx];
        m_buckets[idx] = newnode;
        ++m_size;
        return iterator(newnode, this);
    }
    size_t erase(const key_type &key)
    {
        size_t idx = m_hash(key) % m_buckets.size();
        if (m_buckets[idx] == nullptr) {
            return 0;
        }
        if (m_getkey(m_buckets[idx]->value) == key) {
            node *tmp = m_buckets[idx];
            m_buckets[idx] = tmp->next;
            std::destroy_at(&tmp->value);
            dealloc_node(tmp);
            --m_size;
            return 1;
        }
        node *cur = m_buckets[idx];
        node *next = cur->next;
        while (next != nullptr) {
            if (m_getkey(next->value) == key) {
                cur->next = next->next;
                std::destroy_at(&next->value);
                dealloc_node(next);
                --m_size;
                return 1;
            }
            cur = next;
            next = next->next;
        }
        return 0;
    }
    iterator find(const key_type &key)
    {
        size_t idx = m_hash(key) % m_buckets.size();
        for (node *cur = m_buckets[idx]; cur != nullptr; cur = cur->next) {
            if (m_getkey(cur->value) == key) {
                return iterator(cur, this);
            }
        }
        return end();
    }

    iterator begin()
    {
        for (size_t i = 0; i < m_buckets.size(); ++i) {
            if (m_buckets[i]) {
                return iterator(m_buckets[i], this);
            }
        }
        return iterator(nullptr, this);
    }
    iterator begin() const
    {
        for (size_t i = 0; i < m_buckets.size(); ++i) {
            if (m_buckets[i]) {
                return iterator(m_buckets[i], this);
            }
        }
        return iterator(nullptr, this);
    }
    iterator end()
    {
        return iterator(nullptr, this);
    }
    iterator end() const
    {
        return iterator(nullptr, this);
    }




};

























}
#endif //TSINGHUA_DSA_INCLUDE_DSA_HASHTABLE_HPP
