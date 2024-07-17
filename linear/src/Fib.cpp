//
// Created by shiqing on 2020/5/7.
//

#include "Fib.h"

Fib::Fib(int n) : g_(0), f_(1)
{
    while (g_ < n)
    {
        g_ += f_;
        f_ = g_ - f_;
    }
}

int Fib::get() const
{
    return g_;
}

int Fib::next()
{
    g_ += f_;
    f_ = g_ - f_;
    return g_;
}

int Fib::pre()
{
    f_ = g_ - f_;
    g_ -= f_;
    return g_;
}
