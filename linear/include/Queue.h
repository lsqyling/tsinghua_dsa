//
// Created by shiqing on 19-5-25.
//

#ifndef TSINGHUA_DATASTRUCTURE_QUEUE_H
#define TSINGHUA_DATASTRUCTURE_QUEUE_H

#include "List.h"

namespace linear {

template<typename T>
class Queue
{
    friend std::ostream &operator<<(std::ostream &os, const Queue<T> &rhs)
    {
        return os << rhs.lt;
    }

    friend bool operator==(const Queue<T> &lhs, const Queue<T> &rhs)
    {
        return rhs.lt == lhs.lt;
    }

    friend bool operator!=(const Queue<T> &lhs, const Queue<T> &rhs)
    {
        return lhs.lt != rhs.lt;
    }

public:
    long size() const noexcept
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

    T &front() noexcept
    {
        return lt.front();
    }

private:
    List<T> lt;
};

}

#endif //TSINGHUA_DATASTRUCTURE_QUEUE_H
