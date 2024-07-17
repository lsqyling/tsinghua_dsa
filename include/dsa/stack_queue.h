//
// Created by shiqing on 2020/5/21.
//

#ifndef TSINGHUA_DATASTRUCTURE_STACK_QUEUE_H
#define TSINGHUA_DATASTRUCTURE_STACK_QUEUE_H

#include "Vector.h"
#include "List.h"

namespace linear {
template<typename T>
class stack
{
    friend std::ostream &operator<<(std::ostream &os, const stack<T> &rhs)
    {
        printf("%c", '[');
        for (auto it = rhs.vt.end() - 1; it != rhs.vt.begin() - 1; --it)
        {
            os << *it << " ";
        }
        printf("%c", ']');
        return os;
    }

    friend bool operator==(const stack<T> &lhs, const stack<T> &rhs)
    {
        return lhs.vt == rhs.vt;
    }

    friend bool operator!=(const stack<T> &lhs, const stack<T> &rhs)
    {
        return lhs.vt != rhs.vt;
    }

public:
    void push(const T &t)
    {
        vt.pushBack(t);
    }

    T pop()
    {
        return vt.popBack();
    }

    T &top()
    {
        return vt.at(vt.size() - 1);
    }

    const T &top() const
    {
        return vt.at(vt.size() - 1);
    }

    bool empty() const noexcept
    {
        return vt.empty();
    }

    void clear()
    {
        while (!empty()) pop();
    }

    int size() const noexcept
    {
        return vt.size();
    }

private:
    Vector<T> vt;
};

template<typename T>
class queue
{
    friend std::ostream &operator<<(std::ostream &os, const queue<T> &rhs)
    {
        return os << rhs.lt;
    }

    friend bool operator==(const queue<T> &lhs, const queue<T> &rhs)
    {
        return rhs.lt == lhs.lt;
    }

    friend bool operator!=(const queue<T> &lhs, const queue<T> &rhs)
    {
        return lhs.lt != rhs.lt;
    }

public:
    int size() const noexcept
    {
        return lt.size();
    }

    bool empty() const noexcept
    {
        return lt.empty();
    }

    void enqueue(const T &e)
    {
        lt.pushBack(e);
    }

    T dequeue() noexcept
    {
        T t = lt.front();
        lt.popFront();
        return t;
    }

    T &front()
    {
        return lt.front();
    }

    const T &front() const
    {
        return lt.front();
    }

private:
    List<T> lt;
};

}
#endif //TSINGHUA_DATASTRUCTURE_stack_H
