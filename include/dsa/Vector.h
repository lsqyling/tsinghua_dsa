//
// Created by shiqing on 19-5-18.
//

#ifndef TSINGHUA_DATASTRUCTURE_VECTOR_H
#define TSINGHUA_DATASTRUCTURE_VECTOR_H

#include <initializer_list>
#include <utility>
#include <type_traits>
#include <typeinfo>
#include <iostream>

namespace linear {

namespace UtilityV {
template<typename T, typename...Args>
inline void constructAt(T *ptr, Args &&...args)
{
    new(ptr) T(std::forward<Args>(args)...);
}

template<typename InIterator, typename OutIterator>
OutIterator uninitializedCopy(InIterator beg, InIterator end, OutIterator first)
{
    while (beg != end)
    {
        constructAt(first, *beg);
        ++beg, ++first;
    }
    return first;
}

template<typename T, typename...Args>
T *uninitializedMoveValues(std::size_t n, T *ptr, Args &&...args)
{
    while (n--)
    {
        constructAt(ptr++, std::forward<Args>(args)...);
    }
    return ptr;
}

template<typename InIterator, typename OutIterator>
OutIterator uninitializedMove(InIterator beg, InIterator end, OutIterator first)
{
    while (beg != end)
    {
        constructAt(first, std::move(*beg));
        ++beg, ++first;
    }
    return first;
}

template<typename InIterator, typename OutIterator, typename T>
void rCopy(InIterator beg, InIterator end, OutIterator last, const T &val)
{
    while (end != beg)
    {
        *last = *(end - 1);
        --last, --end;
    }
    constructAt(last, val);
}

template<typename InIterator, typename OutIterator>
OutIterator copy(InIterator beg, InIterator end, OutIterator first)
{
    while (beg != end)
    {
        *first++ = *beg++;
    }
    return first;
}

template<typename T>
inline void destroyAt(T *ptr) noexcept
{
    ptr->~T();
}

template<typename Iter>
void destroyRange(Iter beg, Iter end)
{
    while (end != beg)
    {
        destroyAt(end - 1);
        --end;
    }
}

}


template<typename T>
class Vector
{
    friend std::ostream &operator<<(std::ostream &os, const Vector &rhs)
    {
        if (typeid(T) == typeid(char))
        {
            for (auto pT = rhs.begin(); pT != rhs.end(); ++pT)
            {
                os << *pT;
            }
        }
        else
        {
            for (auto pT = rhs.begin(); pT != rhs.end(); ++pT)
            {
                os << *pT << " ";
            }
        }
        return os;
    }

    friend bool operator==(const Vector &lhs, const Vector &rhs)
    {
        if (lhs.size() != rhs.size()) return false;
        for (decltype(lhs.size()) i = 0; i != lhs.size(); ++i)
        {
            if (lhs[i] != rhs[i]) return false;
        }
        return true;
    }

    friend bool operator!=(const Vector &lhs, const Vector &rhs)
    {
        return !(lhs == rhs);
    }

public:
    using SizeT = std::size_t;
    using Iterator = T *;
    template<typename InIter>
    using RequireInputIter = typename
    std::enable_if_t<
            std::is_convertible<
                    typename std::iterator_traits<InIter>::iterator_category, std::input_iterator_tag
            >::value
    >;

    Vector() : bufBegin_(nullptr), bufEnd_(nullptr), usageCapacity_(nullptr)
    {
    }

    Vector(std::initializer_list<T> li);

    template<typename... Args>
    explicit Vector(SizeT n, Args &&...args);

    template<typename InIter, typename = RequireInputIter<InIter>>
    Vector(InIter beg, InIter end);

    template<unsigned M>
    explicit Vector(const T (&arr)[M]) : Vector(std::begin(arr), std::end(arr))
    {
    }

    Vector(const Vector &rhs);

    Vector(Vector &&rhs) noexcept;

    Vector &operator=(const Vector &rhs) &;

    Vector &operator=(Vector &&rhs) &;

    ~Vector();

    Iterator begin() const noexcept
    {
        return bufBegin_;
    }

    Iterator end() const noexcept
    {
        return bufEnd_;
    }

    SizeT size() const noexcept
    {
        return bufEnd_ - bufBegin_;
    }

    bool empty() const noexcept
    {
        return size() == 0;
    }

    SizeT capacity() const noexcept
    {
        return usageCapacity_ - bufBegin_;
    }

    T &operator[](SizeT pos);

    const T &operator[](SizeT pos) const;

    T &at(SizeT pos);

    const T &at(SizeT pos) const;

    void pushBack(const T &t);

    void pushBack(T &&t);

    T popBack() noexcept;

    template<typename ...Args>
    void emplaceBack(Args &&... args);

    SizeT insert(SizeT pos, const T &t);

    Iterator insert(Iterator iter, const T &t);

    SizeT erase(SizeT pos, int n = 1);

    SizeT erase(Iterator beg, Iterator end);

    SizeT erase(SizeT lo, SizeT hi);

    /*
     * algorithm
     */
    int find(T val) const noexcept;

    void sort() noexcept;

    int search(T val) const noexcept;

    void duplicate();

    int uniquely();

protected:
    void check();

    void adjustCapacity(std::size_t n);

    void clear();

private:
    T *allocateRawMemory(SizeT n);

    void deallocateRawMemory();

    T *bufBegin_, *bufEnd_, *usageCapacity_;

};


template<typename T>
Vector<T>::Vector(std::initializer_list<T> li)
{
    auto sz = li.size();
    bufBegin_ = allocateRawMemory(sz);
    bufEnd_ = UtilityV::uninitializedCopy(li.begin(), li.end(), bufBegin_);
    usageCapacity_ = bufEnd_;
}

template<typename T>
template<typename... Args>
Vector<T>::Vector(Vector::SizeT n, Args &&... args)
{
    bufBegin_ = allocateRawMemory(n);
    bufEnd_ = UtilityV::uninitializedMoveValues(n, bufBegin_, std::forward<Args>(args)...);
    usageCapacity_ = bufEnd_;
}

template<typename T>
template<typename InIter, typename>
Vector<T>::Vector(InIter beg, InIter end)
{
    bufBegin_ = allocateRawMemory(end - beg);
    bufEnd_ = UtilityV::uninitializedCopy(beg, end, bufBegin_);
    usageCapacity_ = bufEnd_;
}

template<typename T>
Vector<T>::Vector(const Vector &rhs)
{
    bufBegin_ = allocateRawMemory(rhs.bufEnd_ - rhs.bufBegin_);
    bufEnd_ = UtilityV::uninitializedCopy(rhs.begin(), rhs.end(), bufBegin_);
    usageCapacity_ = bufEnd_;
}

template<typename T>
Vector<T>::Vector(Vector &&rhs) noexcept : bufBegin_(rhs.bufBegin_), bufEnd_(rhs.bufEnd_),
                                           usageCapacity_(rhs.usageCapacity_)
{
    rhs.bufBegin_ = rhs.bufEnd_ = rhs.usageCapacity_ = nullptr;
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector &rhs) &
{
    if (this != &rhs)
    {
        clear();
        bufBegin_ = allocateRawMemory(rhs.bufEnd_ - rhs.bufBegin_);
        bufEnd_ = UtilityV::uninitializedCopy(rhs.begin(), rhs.end(), bufBegin_);
        usageCapacity_ = bufEnd_;
    }
    return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator=(Vector &&rhs) &
{
    if (this != &rhs)
    {
        clear();
        bufBegin_ = rhs.bufBegin_;
        bufEnd_ = rhs.bufEnd_;
        usageCapacity_ = rhs.usageCapacity_;
        rhs.bufBegin_ = rhs.bufEnd_ = rhs.usageCapacity_ = nullptr;
    }
    return *this;
}

template<typename T>
Vector<T>::~Vector()
{
    clear();
}

template<typename T>
inline T &Vector<T>::operator[](Vector::SizeT pos)
{
    return *(bufBegin_ + pos);
}

template<typename T>
inline const T &Vector<T>::operator[](Vector::SizeT pos) const
{
    return *(bufBegin_ + pos);
}

template<typename T>
T &Vector<T>::at(Vector::SizeT pos)
{
    if (pos > bufEnd_ - bufBegin_)
    {
        throw std::range_error("Out of the range");
    }
    return *(bufBegin_ + pos);
}

template<typename T>
inline const T &Vector<T>::at(Vector::SizeT pos) const
{
    if (pos > (bufEnd_ - bufBegin_))
    {
        throw std::range_error("Out of the range");
    }
    return *(bufBegin_ + pos);
}

template<typename T>
void Vector<T>::pushBack(const T &t)
{
    check();
    UtilityV::constructAt(bufEnd_++, t);
}

template<typename T>
void Vector<T>::pushBack(T &&t)
{
    check();
    UtilityV::constructAt(bufEnd_++, std::move(t));
}

template<typename T>
T Vector<T>::popBack() noexcept
{
    T t = *--bufEnd_;
    check();
    return t;
}

template<typename T>
template<typename... Args>
void Vector<T>::emplaceBack(Args &&... args)
{
    check();
    UtilityV::constructAt(bufEnd_++, std::forward<Args>(args)...);
}

template<typename T>
typename Vector<T>::SizeT Vector<T>::insert(Vector::SizeT pos, const T &t)
{
    if (pos > size()) throw std::range_error("out of range");
    check();
    UtilityV::rCopy(bufBegin_ + pos, bufEnd_, bufEnd_, t);
    ++bufEnd_;
    return pos;
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::insert(Vector::Iterator iter, const T &t)
{
    SizeT n = iter - bufBegin_;
    check();
    UtilityV::rCopy(bufBegin_ + n, bufEnd_, bufEnd_, t);
    ++bufEnd_;
    return bufBegin_ + n;
}

template<typename T>
typename Vector<T>::SizeT Vector<T>::erase(Vector::SizeT pos, int n)
{
    if (pos + n < size())
    {
        erase(bufBegin_ + pos, bufBegin_ + pos + n);
        check();
        return n;
    }
    else
    {
        erase(bufBegin_ + pos, bufEnd_);
        check();
        return bufEnd_ - (bufBegin_ + pos);
    }
}

template<typename T>
typename Vector<T>::SizeT Vector<T>::erase(Vector::Iterator beg, Vector::Iterator end)
{
    SizeT n = end - beg;
    bufEnd_ = UtilityV::copy(end, bufEnd_, beg);
    check();
    return n;
}

template<typename T>
typename Vector<T>::SizeT Vector<T>::erase(Vector::SizeT lo, Vector::SizeT hi)
{
    erase(bufBegin_ + lo, bufBegin_ + hi);
    return hi - lo;
}

template<typename T>
void Vector<T>::check()
{
    if (bufEnd_ == usageCapacity_)
    {
        return adjustCapacity(2 * size());
    }
    if ((bufEnd_ - bufBegin_) * 4 < usageCapacity_ - bufBegin_)
    {
        return adjustCapacity(capacity() / 2);
    }
}

template<typename T>
void Vector<T>::adjustCapacity(size_t n)
{
    if (n == 0) n = 1;
    auto newBufBegin = allocateRawMemory(n);
    auto newBufEnd = UtilityV::uninitializedMove(bufBegin_, bufEnd_, newBufBegin);
    UtilityV::destroyRange(bufBegin_, bufEnd_);
    deallocateRawMemory();
    bufBegin_ = newBufBegin;
    bufEnd_ = newBufEnd;
    usageCapacity_ = bufBegin_ + n;
}

template<typename T>
void Vector<T>::clear()
{
    UtilityV::destroyRange(bufBegin_, bufEnd_);
    deallocateRawMemory();
    bufBegin_ = bufEnd_ = usageCapacity_ = nullptr;
}

template<typename T>
inline T *Vector<T>::allocateRawMemory(Vector::SizeT n)
{
    return static_cast<T *>(::operator new(n * sizeof(T)));
}

template<typename T>
inline void Vector<T>::deallocateRawMemory()
{
    ::operator delete(bufBegin_);
}

namespace helperV {
template<typename T>
int find(T val, int lo, int hi, T *buf) noexcept
{
    for (int i = lo; i < hi; ++i)
    {
        if (val == buf[i])
        {
            return i;
        }
    }
    return -1;
}

template<typename T>
inline void swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template<typename T>
int bubble(int lo, int hi, T *buf)
{
    int last = lo;
    while (++lo < hi)
    {
        if (buf[lo] < buf[lo - 1])
        {
            swap(buf[lo - 1], buf[lo]);
            last = lo;
        }
    }
    return last;
}

template<typename T>
void bubbleSort(int lo, int hi, T *buf)
{
    while (lo < (hi = bubble(lo, hi, buf)));
}

template<typename T>
void merge(int lo, int mid, int hi, T *buf)
{
    auto auxBuf = new T[mid - lo];
    for (int i = lo, j = 0; i < mid; ++i)
    {
        auxBuf[j++] = buf[i];
    }
    for (int k = lo, i = 0, j = mid; i < (mid - lo) || j < hi;)
    {
        auxBuf[i] <= buf[j] ? buf[k++] = auxBuf[i++] : buf[k++] = buf[j++];
        if (i == mid - lo)
            break;
        while (j == hi && i < mid - lo)
        {
            buf[k++] = auxBuf[i++];
        }
    }
    delete[] auxBuf;
}

template<typename T>
void mergeSort(int lo, int hi, T *buf)
{
    if (hi - lo < 2) return;
    int mid = lo + (hi - lo) / 2;
    mergeSort(lo, mid, buf);
    mergeSort(mid, hi, buf);
    merge(lo, mid, hi, buf);
}

template<typename T>
int search(T val, int lo, int hi, T *buf) noexcept
{
    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        val < buf[mid] ? hi = mid : lo = mid + 1;
    }
    return lo - 1;
}

template<typename T>
T *uniquely(int lo, int hi, T *buf) noexcept
{
    int i = lo, j = lo;
    while (++j < hi)
    {
        if (buf[i] != buf[j])
        {
            buf[++i] = buf[j];
        }
    }
    return buf + ++i;
}

}

template<typename T>
void Vector<T>::sort() noexcept
{
    size_t rand = random();
    if (rand & 1U) helperV::mergeSort(0, size(), bufBegin_);
    else helperV::bubbleSort(0, size(), bufBegin_);
}

/**
 * The invariance: A[0, lo) <= e < A[hi, n)
 * the monotonicity:
 * @return the last of element that is not bigger than val;
 */
template<typename T>
int Vector<T>::search(T val) const noexcept
{
    return helperV::search(val, 0, size(), bufBegin_);
}

template<typename T>
int Vector<T>::find(T val) const noexcept
{
    return helperV::find(val, 0, size(), bufBegin_);
}

template<typename T>
void Vector<T>::duplicate()
{
    for (int i = 1; i < size();)
    {
        int pos = helperV::find(bufBegin_[i], 0, i, bufBegin_);
        if (pos == -1) ++i;
        else erase(pos);
    }
}

template<typename T>
int Vector<T>::uniquely()
{
    auto e = bufEnd_;
    bufEnd_ = helperV::uniquely(0, size(), bufBegin_);
    int n = e - bufEnd_;
    check();
    return n;
}

}

#endif //TSINGHUA_DATASTRUCTURE_VECTOR_H
