//
// Created by 10580.
//

#ifndef TSINGHUA_DSA_INCLUDE_DSA_LIST_HPP
#define TSINGHUA_DSA_INCLUDE_DSA_LIST_HPP
#include <iterator>
#include <concepts>
#include <iostream>
#include "allocator.hpp"
namespace ds {
template<typename T>
struct listnode
{
    listnode *next;
    listnode *prev;
    T data;
};

template<typename T, typename Alloc = allocator<listnode<T>>> class list;

template<typename T>
class list_iterator
{
    friend class list<T>;
public:
    using value_type        = T;
    using pointer           = value_type *;
    using reference         = value_type &;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type   = std::ptrdiff_t;

    using node     = listnode<T>;
    using iterator = list_iterator;

private:
    node *mp_node;

public:
    list_iterator() noexcept : mp_node(nullptr) {}
    list_iterator(node *const pnode) noexcept : mp_node(pnode) {}

    reference operator*() const noexcept { return mp_node->data; }
    node *operator->() const noexcept { return mp_node; }
    bool operator==(const iterator &other) const noexcept { return mp_node == other.mp_node; }
    bool operator!=(const iterator &other) const noexcept { return !( *this == other ); }
    iterator &operator++() noexcept
    {
        mp_node = mp_node->next;
        return *this;
    }
    iterator operator++(int) noexcept
    {
        auto tmp = *this;
        ++*this;
        return tmp;
    }
    iterator &operator--() noexcept
    {
        mp_node = mp_node->prev;
        return *this;
    }
    iterator operator--(int) noexcept
    {
        auto tmp = *this;
        --*this;
        return tmp;
    }
};

template<typename T, typename Alloc>
class list
{
public:
    using value_type      = T;
    using pointer         = value_type *;
    using reference       = value_type &;
    using iterator        = list_iterator<T>;
    using difference_type = std::ptrdiff_t;

    using node  = listnode<T>;

private:
    node *mp_dummy;

    iterator insert_after(iterator pos, const value_type &value)
    {
        node *newnode = create_node(value);
        newnode->next = pos.mp_node->next;
        pos.mp_node->next->prev = newnode;

        pos.mp_node->next = newnode;
        newnode->prev = pos.mp_node;

        return newnode;
    }

    static node *alloc_node()
    {
        return Alloc::allocate(1);
    }
    static void dealloc_node(node *pnode)
    {
        Alloc::deallocate(pnode);
    }
    static node *create_node(const value_type &value)
    {
        node *newnode = alloc_node();
        allocator<value_type >::construct(&newnode->data, value);
        return newnode;
    }

public:
    list() noexcept
    {
        mp_dummy = alloc_node();
        mp_dummy->next = mp_dummy;
        mp_dummy->prev = mp_dummy;
    }
    list(std::initializer_list<T> init_list) : list()
    {
        insert(end(), init_list.begin(), init_list.end());
    }
    list(const list &other) noexcept : list()
    {
        insert(begin(), other.begin(), other.end());
    }
    list(list &&other) noexcept : list()
    {
        if (other.empty())
            return ;
        mp_dummy->prev = other.mp_dummy->prev;
        mp_dummy->next = other.mp_dummy->next;
        other.mp_dummy->next->prev = mp_dummy;
        other.mp_dummy->prev->next = mp_dummy;

        other.mp_dummy->next = other.mp_dummy;
        other.mp_dummy->prev = other.mp_dummy;
    }
    list &operator=(const list &other)
    {
        if (this->mp_dummy == other.mp_dummy)
            return *this;
        clear();
        insert(begin(), other.begin(), other.end());
        return *this;
    }
    list &operator=(list &&other) noexcept
    {
        if (this->mp_dummy == other.mp_dummy)
            return *this;
        clear();
        mp_dummy->prev = other.mp_dummy->prev;
        mp_dummy->next = other.mp_dummy->next;
        other.mp_dummy->prev->next = mp_dummy;
        other.mp_dummy->next->prev = mp_dummy;

        other.mp_dummy->next = other.mp_dummy;
        other.mp_dummy->prev = other.mp_dummy;

        return *this;
    }


    iterator insert(iterator pos, const value_type &value)
    {
        node *newnode = create_node(value);
        newnode->prev = pos.mp_node->prev;
        pos.mp_node->prev->next = newnode;

        newnode->next = pos.mp_node;
        pos.mp_node->prev = newnode;

        return newnode;
    }

    iterator insert(iterator pos, size_t count, const value_type &value)
    {
        auto it = pos;
        for (size_t i = 0; i < count; ++i) {
            it = insert(it, value);
        }
        return it;
    }
    template<std::input_iterator Input>
    iterator insert(iterator pos, Input first, Input last)
    {
        iterator it = --pos;
        iterator first_prev = it;
        for (; first != last; ++first) {
            it = insert_after(it, *first);
        }
        return ++first_prev;
    }

    iterator erase(iterator pos)
    {
        node *prevnode = pos.mp_node->prev;
        node *nextnode = pos.mp_node->next;
        prevnode->next = nextnode;
        nextnode->prev = prevnode;

        allocator<T>::destroy(&pos->data);
        dealloc_node(pos.mp_node);
        return nextnode;
    }
    iterator erase(iterator first, iterator last)
    {
        iterator it = first;
        while (it != last) {
            it = erase(it);
        }
        return it;
    }
    void clear()
    {
        auto it = begin();
        while (it != end()) {
            node *tmp = it.mp_node;
            ++it;
            allocator<T>::destroy(&tmp->data);
            dealloc_node(tmp);
        }
        mp_dummy->next = mp_dummy;
        mp_dummy->prev = mp_dummy;
    }
    ~list() noexcept
    {
        clear();
        dealloc_node(mp_dummy);
    }
    void assign(size_t count, const value_type &value)
    {
        size_t len = 0;
        iterator it;
        for (it = begin(); it != end() && len < count; ++it, ++len) {
            *it = value;
        }
        if (len < count) {
            insert(end(), count - len, value);
        } else {
            erase(it, end());
        }
    }
    void resize(size_t count, const value_type &value)
    {
        size_t len = 0;
        iterator it = begin();
        for ( ; it != end() && len < count; ++it, ++len) ;
        if (len < count) {
            insert(end(), count - len, value);
        } else {
            erase(it, end());
        }
    }
    void resize(size_t count)
    {
        resize(count, value_type{});
    }
    reference front() { return *begin(); }
    reference back() { return *--end(); }
    [[nodiscard("no used returned?")]]
    bool empty() const { return begin() == end(); }
    [[nodiscard("no used returned?")]]
    size_t size() const
    {
        size_t count = 0;
        for (auto it = begin(); it != end(); ++it, ++count);
        return count;
    }
    void push_back(const value_type &value) { insert(end(), value); }
    void push_front(const value_type &value) { insert(begin(), value); }
    void pop_back() { erase(--end()); }
    void pop_front() { erase(begin()); }

    iterator begin() const { return mp_dummy->next; }
    iterator begin() { return mp_dummy->next; }
    iterator end() const { return mp_dummy; }
    iterator end() { return mp_dummy; }


    void show() const
    {
        for (iterator it = begin(); it != end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "\n";
    }
};
}

#endif //TSINGHUA_DSA_INCLUDE_DSA_LIST_HPP