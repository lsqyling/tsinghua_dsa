//
// Created by shiqing on 19-7-16.
//

#ifndef TSINGHUA_DATASTRUCTURE_JOSEPHUS_H
#define TSINGHUA_DATASTRUCTURE_JOSEPHUS_H

namespace josephus {

class Josephus
{
    friend void Solve();

public:
    explicit Josephus(int nTheItems)
            : pQ_(new int[nTheItems * 2]),
              size_(0), head_(0), tail_(0), len_(nTheItems * 2), number_(nTheItems)
    {
        init();
    }

    Josephus(const Josephus &) = delete;

    Josephus &operator=(const Josephus &) = delete;

    int solve();

    ~Josephus()
    {
        delete[] pQ_;
    }

private:
    void enqueue(int x);

    int dequeue();

    void init();

private:
    int *pQ_;
    int size_, head_, tail_;
    int len_, number_;
};

void Solve();
}

#endif //TSINGHUA_DATASTRUCTURE_JOSEPHUS_H
