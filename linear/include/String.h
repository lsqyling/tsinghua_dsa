//
// Created by shiqing on 19-5-21.
//

#ifndef TSINGHUA_DATASTRUCTURE_STRING_H
#define TSINGHUA_DATASTRUCTURE_STRING_H

#include <string>
#include "Vector.h"

namespace linear {

template<typename T>
class BasicStr : public Vector<T>
{
public:
    using Vector<T>::Vector;

    template<unsigned M>
    BasicStr(const char (&arr)[M]) : BasicStr(std::begin(arr), std::end(arr))
    {
    }

    BasicStr(const char *cp);

    BasicStr(const std::string &s) : BasicStr(s.begin(), s.end())
    {
    }

    operator std::string() const noexcept
    {
        return std::string(this->begin(), this->end());
    }

    const char *c_str() const noexcept;

    int indexOf(const BasicStr &rhs) const noexcept;

};

template<typename T>
BasicStr<T>::BasicStr(const char *cp)
{
    if (cp)
    {
        while (*cp)
        {
            this->pushBack(*cp++);
        }
    }
}

/**
  *  @brief  Return const pointer to contents.
  *
  *  This is a handle to internal data.  Do not modify or dire things may
  *  happen.
 */
template<typename T>
inline const char *BasicStr<T>::c_str() const noexcept
{
    const_cast<BasicStr<T> *>(this)->pushBack('\0');
    return this->begin();
}

template<typename T>
int BasicStr<T>::indexOf(const BasicStr &subStr) const noexcept
{
    int n = this->size(), m = subStr.size();
    if (n < m) return -1;
    int i, j;
    for (i = 0, j = 0; i < n && j < m;)
    {
        if ((*this)[i] == subStr[j])
        {
            ++i;
            ++j;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == m) return i - j;
    return -1;
}

using String = BasicStr<char>;

template<typename T>
int indexOf(const BasicStr<T> &s, const BasicStr<T> &rhs) noexcept
{
    int n = s.size(), m = rhs.size();
    if (n < m) return -1;
    int j;
    for (int i = 0; i < n - m + 1; ++i)
    {
        for (j = 0; j < m; ++j)
        {
            if (s[i + j] != rhs[j]) break;
        }
        if (j == m) return i;
    }
    return -1;
}

template<typename T>
int *getNext(const BasicStr<T> &s)
{
    int *next = new int[s.size()];
    int j = next[0] = -1;
    for (int i = 1; i < s.size(); ++i)
    {
        while (j != -1 && s[i] != s[j + 1])
        {
            j = next[j];
        }

        if (s[i] == s[j + 1])
        {
            ++j;
        }
        next[i] = j;
    }
    return next;
}

template<typename T>
int indexOfUsingKMP(const BasicStr<T> &text, const BasicStr<T> &pattern) noexcept
{
    int *next = getNext(pattern), r = -1;
    int j = next[0];
    for (int i = 0; i < text.size(); ++i)
    {
        while (j != -1 && text[i] != pattern[j + 1])
        {
            j = next[j];
        }

        if (text[i] == pattern[j + 1]) ++j;

        if (j == pattern.size() - 1)
        {
            r = i - j;
            break;
        }
    }
    delete[] next;
    return r;
}

}

#endif //TSINGHUA_DATASTRUCTURE_STRING_H
