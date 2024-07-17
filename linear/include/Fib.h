//
// Created by shiqing on 2020/5/7.
//

#ifndef TSINGHUA_DATASTRUCTURE_FIB_H
#define TSINGHUA_DATASTRUCTURE_FIB_H

class Fib
{
public:
    /*
     * 初始化为不小于n的最小Fibonacci项
     */
    explicit Fib(int n);

    int get() const;

    int next();

    int pre();

private:
    int g_, f_;
};

#endif //TSINGHUA_DATASTRUCTURE_FIB_H
