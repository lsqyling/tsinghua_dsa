//
// Created by 10580.
//

#ifndef TSINGHUA_DSA_INCLUDE_DSA_VECTOR_HPP
#define TSINGHUA_DSA_INCLUDE_DSA_VECTOR_HPP
#include <concepts>
#include <format>
#include "allocator.hpp"

namespace ds {
template<typename T, typename Alloc = allocator<T>>
class vector
{
public:
    using value_type        =       T;
    using pointer           =       value_type *;
    using reference         =       value_type &;
    using const_reference   =       const value_type &;
    using difference_type   =       std::ptrdiff_t;
    using iterator          =       value_type *;
    using const_iterator    =       const value_type *;

private:
    T * m_begin;
    T * m_end;
    T * m_capacity;

public:
    vector() noexcept : m_begin(nullptr), m_end(nullptr), m_capacity(nullptr) {}
    ~vector() // default as noexcept
    {
        std::destroy(begin(), end());
        Alloc::deallocate(m_begin);
    }
    vector(size_t n, const value_type &value)
    {
        m_begin = Alloc::allocate(n);
        std::uninitialized_fill_n(m_begin, n, value);
        m_end = m_capacity = m_begin + n;
    }
    template<std::input_iterator Input>
    vector(Input first, Input last)
    {
        size_t n = std::distance(first, last);
        m_begin = Alloc::allocate(n);
        std::uninitialized_copy(first, last, m_begin);
        m_end = m_capacity = m_begin + n;
    }
    vector(std::initializer_list<T> list) : vector(list.begin(), list.end()) {}
    vector(const vector &other) noexcept : vector(other.begin(), other.end()) {}
    vector(vector &&other) noexcept
    {
        m_begin = other.m_begin;
        m_end = other.m_end;
        m_capacity = other.m_capacity;
        other.m_begin = other.m_end = other.m_capacity = nullptr;
    }

    vector &operator=(const vector &other) noexcept
    {
        if (this == &other)
            return *this;
        if (other.size() > capacity()) {
            vector tmp(other);
            tmp.swap(*this);
        } else if (other.size() > size()) {
            std::copy(other.begin(), other.begin() + size(), m_begin);
            m_end = std::uninitialized_copy(other.begin() + size(), other.end(), m_end);
        } else {
            iterator newend = std::copy(other.begin(), other.end(), m_begin);
            std::destroy(newend, end());
            m_end = newend;
        }
        return *this;
    }
    vector &operator=(vector &&other) noexcept
    {
        if (this == &other)
            return *this;
        this->swap(other);
        return *this;
    }

    void reserve(size_t n)
    {
        if (capacity() >= n)
            return ;
        iterator newbegin = Alloc::allocate(n);
        iterator newend = std::uninitialized_copy(begin(), end(), newbegin);
        std::destroy(begin(), end());
        Alloc::deallocate(m_begin);
        m_begin = newbegin;
        m_end = newend;
        m_capacity = m_begin + n;
    }

    void swap(vector &other) noexcept
    {
        std::swap(m_begin, other.m_begin);
        std::swap(m_end, other.m_end);
        std::swap(m_capacity, other.m_capacity);
    }

    reference operator[](size_t index)
    {
        return *(begin() + index);
    }
    const_reference operator[](size_t index) const
    {
        return *(begin() + index);
    }
    reference front() { return *begin(); }
    const_reference front() const { return *begin(); }
    reference back() { return *(end() - 1); }
    const_reference back() const { return *(end() - 1); }
    [[nodiscard("no discard")]]
    bool empty() const { return begin() == end(); }

    void clear()
    {
        std::destroy(begin(), end());
        m_end = m_begin;
    }
    iterator insert(iterator pos, size_t n, const value_type &value)
    {
        if (n == 0) return pos;
        if (m_capacity - m_end >= n) {
            size_t elems_after = m_end - pos;
            if (n < elems_after) {
                std::uninitialized_move(m_end - n, m_end, m_end);
                std::move_backward(pos, m_end - n, m_end);
                std::fill_n(pos, n, value);
                m_end += n;
            } else {
                std::uninitialized_move(pos, m_end, pos + n);
                std::fill(pos, m_end, value);
                std::uninitialized_fill(m_end, pos + n, value);
                m_end += n;
            }
            return pos;
        }
        else {
            const size_t newsize = std::max(2 * size(), size() + n);
            iterator newbegin = Alloc::allocate(newsize);
            iterator newpos, newend;
            newpos = newend = std::uninitialized_move(begin(), pos, newbegin);
            newend = std::uninitialized_fill_n(newend, n, value);
            newend = std::uninitialized_move(pos, end(), newend);
            std::destroy(begin(), end());
            Alloc::deallocate(m_begin);
            m_begin = newbegin;
            m_end = newend;
            m_capacity = m_begin + newsize;
            return newpos;
        }
    }
    iterator insert(iterator pos, value_type &&value)
    {
        if (m_end != m_capacity) {
            if (pos != m_end) {
                std::construct_at(m_end, std::move(*(m_end - 1)));
                std::move_backward(pos, m_end - 1, m_end);
                *pos = std::move(value);
                ++m_end;
            } else {
                std::construct_at(m_end, std::move(value));
                ++m_end;
            }
            return pos;
        }
        else {
            size_t newsize = std::max(2 * size(), size() + 1);
            iterator newbegin = Alloc::allocate(newsize);
            iterator newpos, newend;
            newpos = newend = std::uninitialized_move(begin(), pos, newbegin);
            std::construct_at(newend, std::move(value));
            ++newend;
            newend = std::uninitialized_move(pos, end(), newend);
            std::destroy(begin(), end());
            Alloc::deallocate(m_begin);

            m_begin = newbegin;
            m_end = newend;
            m_capacity = m_begin + newsize;

            return newpos;
        }
    }
    iterator insert(iterator pos, const value_type &value)
    {
        if (m_end != m_capacity) {
            if (pos != m_end) {
                std::construct_at(m_end, *(m_end - 1));
                std::move_backward(pos, m_end - 1, m_end);
                *pos = value;
                ++m_end;
            } else {
                std::construct_at(m_end, value);
                ++m_end;
            }
            return pos;
        }
        else {
            size_t newsize = std::max(2 * size(), size() + 1);
            iterator newbegin = Alloc::allocate(newsize);
            iterator newpos, newend;
            newpos = newend = std::uninitialized_move(begin(), pos, newbegin);
            std::construct_at(newend, value);
            ++newend;
            newend = std::uninitialized_move(pos, end(), newend);
            std::destroy(begin(), end());
            Alloc::deallocate(m_begin);

            m_begin = newbegin;
            m_end = newend;
            m_capacity = m_begin + newsize;

            return newpos;
        }
    }
    iterator erase(iterator first, iterator last)
    {
        iterator newend = std::move(last, end(), first);
        std::destroy(newend, end());
        m_end = newend;
        return first;
    }
    iterator erase(iterator pos)
    {
        return erase(pos, pos + 1);
    }
    void resize(size_t n, const value_type &value)
    {
        if (n < size()) {
            erase(begin() + n, end());
        } else {
            insert(end(), n - size(), value);
        }
    }
    void resize(size_t n)
    {
        resize(n, value_type{});
    }
    void push_back(const value_type &value)
    {
        insert(end(), value);
    }
    void push_back(value_type &&value)
    {
        insert(end(), std::move(value));
    }
    void pop_back()
    {
        --m_end;
        std::destroy_at(m_end);
    }

    [[nodiscard("no used returned?")]]
    size_t size() const noexcept { return m_end - m_begin; }
    [[nodiscard("no used returned?")]]
    size_t capacity() const noexcept { return m_capacity - m_begin; }
    iterator begin() noexcept { return m_begin; }
    const_iterator begin() const noexcept { return m_begin; }
    iterator end() noexcept { return m_end; }
    const_iterator end() const noexcept { return m_end; }

    void show() const
    {
        std::cout << "[";
        for (const value_type &val : *this) {
            std::cout << val << " ";
        }
        std::cout << "]\n";
        std::cout << std::format("size = {}, capacity = {}\n", size(), capacity());
    }
};
}

#endif //TSINGHUA_DSA_INCLUDE_DSA_VECTOR_HPP
