//
// Created by shiqing on 19-5-25.
//

#ifndef TSINGHUA_DATASTRUCTURE_STACK_H
#define TSINGHUA_DATASTRUCTURE_STACK_H

#include "Vector.h"

namespace linear {

template<typename T>
class Stack
{
    friend std::ostream &operator<<(std::ostream &os, const Stack<T> &rhs)
    {
        printf("%c", '[');
        for (auto it = rhs.vt.end() - 1; it != rhs.vt.begin() - 1; --it)
        {
            os << *it << " ";
        }
        printf("%c", ']');
        return os;
    }

    friend bool operator==(const Stack<T> &lhs, const Stack<T> &rhs)
    {
        return lhs.vt == rhs.vt;
    }

    friend bool operator!=(const Stack<T> &lhs, const Stack<T> &rhs)
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

    bool empty() const noexcept
    {
        return vt.empty();
    }

    void clear()
    {
        while (!empty()) pop();
    }

    size_t size() const noexcept
    {
        return vt.size();
    }

private:
    Vector<T> vt;

};


}

#endif //TSINGHUA_DATASTRUCTURE_STACK_H
