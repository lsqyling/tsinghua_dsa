//
// Created by shiqing on 2021/5/22.
//

#ifndef TSINGHUA_DATASTRUCTURE_COMMON_UTIL_H
#define TSINGHUA_DATASTRUCTURE_COMMON_UTIL_H
#include <iostream>
#include <cstdint>

namespace bitutil {
template<typename T>
union Bytes
{
    uint8_t contents_[sizeof(T)];
    T t_;
};

bool IsLittleEndian()
{
    union
    {
        int8_t a_[4];
        int32_t b_;
    } e{0};
    e.b_ = 1;
    return e.a_[0] == 1;
}

template<typename T>
std::string GetComplementCode(T val)
{
    Bytes<T> byte{0};
    byte.t_ = val;
    std::string ans{"0x"};
    char tmp[5];
    if (IsLittleEndian())
    {
        for (int i = sizeof(T) - 1; i >= 0; --i)
        {
            sprintf(tmp, "%02x", byte.contents_[i]);
            ans += tmp;
            if (i > 0) ans += " ";
        }
    }
    else
    {
        for (int i = 0; i < sizeof(T); ++i)
        {
            sprintf(tmp, "%02x", byte.contents_[i]);
            ans += tmp;
            if (i < sizeof(T) - 1) ans += " ";
        }
    }
    return ans;
}
}

namespace digit {

std::string num_to_zh(int64_t n);







}



#endif //TSINGHUA_DATASTRUCTURE_COMMON_UTIL_H
