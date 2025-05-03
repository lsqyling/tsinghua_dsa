//
// Created by 10580.
//

#ifndef CPP_COMPLEX_OJ_LEETCODE_UTILITIES_HPP
#define CPP_COMPLEX_OJ_LEETCODE_UTILITIES_HPP
#include <iostream>
#include <utility>
#include <algorithm>
#include <random>
#include <format>
#include <queue>
#include <stack>
#include <limits>
#include <cstdio>
#include <set>
#include <map>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <chrono>


#ifdef _MSC_VER
#define scanf(fmt, ...) scanf_s(fmt, __VA_ARGS__)
#else
#define scanf(fmt, ...) scanf(fmt, ##__VA_ARGS__)
#endif

inline int gen_random(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 engine{rd()};
    std::uniform_int_distribution<int> dist(min, max);

    return dist(engine);
}

inline std::vector<int> gen_rd_array(int n, int min, int max)
{
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        arr[i] = gen_random(min, max);
    }

    return arr;
}

inline bool is_sorted(const std::vector<int> &arr)
{
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; ++i)
    {
        if (arr[i] > arr[i+1])
            return false;
    }
    return true;
}

template<typename T>
inline void print_binary(T n)
{
    int s = sizeof(T) * 8;
    for (int i = s - 1; i >= 0; --i)
    {
        if ((n & (1 << i)) == 0)
            std::cout << "0";
        else
            std::cout << "1";
    }
    std::cout << "\n";
}

inline std::vector<std::string> split(std::string_view str, char delimiter)
{
    std::vector<std::string> ans;
    size_t b = 0;
    size_t e = str.find(delimiter);
    while (e != std::string_view::npos)
    {
        if (e != b)
            ans.emplace_back(str.substr(b, e-b));
        b = e + 1;
        e = str.find(delimiter, b);
    }
    if (b != str.size())
        ans.emplace_back(str.substr(b, e));
    return ans;
}


#endif //CPP_COMPLEX_OJ_LEETCODE_UTILITIES_HPP
