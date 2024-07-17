//
// Created by shiqing on 19-7-16.
//

#include <cstdio>
#include "../include/Josephus.h"

namespace josephus {

void Josephus::init()
{
    for (int i = 1; i <= number_; ++i)
    {
        enqueue(i);
    }
}

void Josephus::enqueue(int x)
{
    if (size_ == 0)
    {
        pQ_[size_] = x;
    }
    else
    {
        tail_ = (tail_ + 1) % len_;
        pQ_[tail_] = x;
    }
    ++size_;
}

int Josephus::dequeue()
{
    int temp = pQ_[head_];
    head_ = (head_ + 1) % len_;
    --size_;
    return temp;
}

int Josephus::solve()
{
    for (int j = 0; j < number_; ++j)
    {
        int x = dequeue();
        dequeue();
        enqueue(x);
    }
    return pQ_[head_];
}

void Solve()
{
    int n, answer;
    printf("Enter the of the numbers of people:");
    scanf("%d", &n);
    Josephus js(n);
    answer = js.solve();
    printf("The value of Josephus(%d) is: %d\n", n, answer);
}

}

