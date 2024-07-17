//
// Created by shiqing on 19-4-11.
//

#ifndef _COMMONHEADERS_H
#define _COMMONHEADERS_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <list>
#include <type_traits>
#include <random>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;
using std::string;

/*
 * print arrays
 */
template<typename T, size_t M>
std::ostream &printArray(std::ostream &os, const T (&arr)[M])
{
    os << '[';
    for (size_t i = 0; i < M; ++i)
    {
        if (i != M - 1) os << arr[i] << ' ';
        else os << arr[i];
    }
    os << ']';
    return os;
}

/*
 * print container
 */
template<typename Container>
std::ostream &printContainer(std::ostream &os, const Container &container)
{
    os << '[';
    for (auto beg = container.begin(); beg != container.end(); ++beg)
    {
        os << *beg << " ";
    }
    os << ']';
    return os;

}

template<typename T>
using RequireNum = std::enable_if_t<std::is_integral<T>::value, T>;

template<int N, typename T = int, typename = RequireNum<T>>
auto generateRandomArray(T init = T()) -> T (&)[N]
{
    static T A[N];
    static std::default_random_engine e(N);
    static std::uniform_int_distribution<T> u(0, N);
    for (int i = 0; i < N; ++i)
    {
        A[i] = u(e);
    }
    return A;
}

template<typename T, int N>
inline bool isSorted(const T (&A)[N]) noexcept
{
    for (int i = 1; i < N; ++i)
    {
        if (A[i] < A[i - 1]) return false;
    }
    return true;
}

template<typename T, int N>
void shuffle(T (&A)[N]) noexcept
{
    static std::default_random_engine e(N);
    static std::uniform_int_distribution<T> u;
    for (int i = N; i > 0; --i)
    {
        std::swap(A[i - 1], A[u(e) % i]);
    }
}

template<typename F, typename... Args>
void calledCostTime(F f, const string &funName, Args &&...params)
{
    auto ts = std::chrono::system_clock::now();
    f(std::forward<Args>(params)...);
    auto te = std::chrono::system_clock::now();
    cout << funName + " cost ( "
         << std::chrono::duration_cast<std::chrono::milliseconds>(te - ts).count()
         << " ) milliseconds\n";
}


#endif //PRIMERADVANCED_COMMONHEADERS_H
