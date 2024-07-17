//
// Created by shiqing on 2020/5/9.
//

#ifndef TSINGHUA_DATASTRUCTURE_SVECTOR_H
#define TSINGHUA_DATASTRUCTURE_SVECTOR_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cassert>

namespace linear {
template<typename T>
class SVector
{
public:
    using Rank = int;

    explicit SVector(int capacity = kDefaultCapacity, int initSz = 0, T defaultV = T());

    SVector(const T *A, int n);

    SVector(const T *A, Rank lo, Rank hi);

    SVector(const SVector &rhs);

    SVector(const SVector &rhs, Rank lo, Rank hi);

    ~SVector()
    {
        delete[] elem_;
    }

    int size() const;

    int capacity() const;

    double loadingFactor() const;

    bool empty() const;

    int disordered() const;

    Rank find(const T &e) const;

    Rank find(const T &e, Rank lo, Rank hi) const;

    Rank search(const T &e) const;

    Rank search(const T &e, Rank lo, Rank hi) const;

    const T &operator[](Rank r) const;

    T &operator[](Rank r);

    SVector &operator=(const SVector &rhs);

    T remove(Rank r);

    int remove(Rank lo, Rank hi);

    Rank insert(Rank r, const T &e);

    Rank insert(const T &e);

    void sort(Rank lo, Rank hi);

    void sort();

    void unsort(Rank lo, Rank hi);

    void unsort();

    int deduplicate();

    int uniquify();

    void traverse(void (*pFun)(T &e));

    template<typename F>
    void traverse(F f);

private:
    static constexpr int kDefaultCapacity = 8;

    void adjustCapacity(int n);

    void check(bool isExpand);

    T *elem_;
    int size_, capacity_;
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const SVector<T> &rhs)
{
    os << '[';
    for (int i = 0; i < rhs.size(); ++i)
    {
        os << rhs[i];
        if (i < rhs.size() - 1) os << " ";
    }
    os << ']';
    return os;
}

template<typename T>
SVector<T>::SVector(int capacity, int initSz, T defaultV) : size_(initSz)
{
    elem_ = new T[capacity_ = capacity];
    for (int i = 0; i < initSz; ++i)
    {
        elem_[i] = defaultV;
    }
}

template<typename T>
SVector<T>::SVector(const T *A, int n) : size_(n)
{
    elem_ = new T[capacity_ = n];
    for (int i = 0; i < n; ++i)
    {
        elem_[i] = A[i];
    }
}

template<typename T>
SVector<T>::SVector(const T *A, SVector::Rank lo, SVector::Rank hi) : size_(hi - lo)
{
    elem_ = new T[capacity_ = size_];
    auto pA = A + lo;
    for (int i = 0; i < size_; ++i)
    {
        elem_[i] = pA[i];
    }
}

template<typename T>
SVector<T>::SVector(const SVector &rhs) : size_(rhs.size_), capacity_(rhs.size_)
{
    elem_ = new T[rhs.size_];
    for (int i = 0; i < size_; ++i)
    {
        elem_[i] = rhs.elem_[i];
    }
}

template<typename T>
SVector<T>::SVector(const SVector &rhs, SVector::Rank lo, SVector::Rank hi) : size_(hi - lo)
{
    elem_ = new T[capacity_ = size_];
    auto pA = rhs.elem_ + lo;
    for (int i = 0; i < size_; ++i)
    {
        elem_[i] = pA[i];
    }
}

template<typename T>
inline int SVector<T>::size() const
{
    return size_;
}

template<typename T>
inline bool SVector<T>::empty() const
{
    return size_ == 0;
}

template<typename T>
inline int SVector<T>::capacity() const
{
    return capacity_;
}

template<typename T>
double SVector<T>::loadingFactor() const
{
    return size_ * 1.0 / capacity_;
}

template<typename T>
int SVector<T>::disordered() const
{
    int r = 0;
    for (int i = 1; i < size_; ++i)
    {
        if (elem_[i - 1] > elem_[i])
        {
            ++r;
        }
    }
    return r;
}

template<typename T>
typename SVector<T>::Rank SVector<T>::find(const T &e) const
{
    return find(e, 0, size_);
}

template<typename T>
typename SVector<T>::Rank SVector<T>::find(const T &e, SVector::Rank lo, SVector::Rank hi) const
{
    while (lo < hi-- && e != elem_[hi]);
    return hi;
}

template<typename T>
typename SVector<T>::Rank SVector<T>::search(const T &e) const
{
    return search(e, 0, size_);
}

template<typename T>
typename SVector<T>::Rank SVector<T>::search(const T &e, SVector::Rank lo, SVector::Rank hi) const
{
    Rank mid;
    while (lo < hi)
    {
        mid = lo + (hi - lo) / 2;
        e < elem_[mid] ? hi = mid : lo = mid + 1;
    }
    return --lo;
}

template<typename T>
inline const T &SVector<T>::operator[](SVector::Rank r) const
{
    return elem_[r];
}

template<typename T>
inline T &SVector<T>::operator[](SVector::Rank r)
{
    return elem_[r];
}

template<typename T>
SVector<T> &SVector<T>::operator=(const SVector &rhs)
{
    auto newElem = new T[capacity_ = rhs.size_];
    size_ = rhs.size_;
    for (int i = 0; i < size_; ++i)
    {
        newElem[i] = rhs.elem_[i];
    }
    delete[] elem_;
    elem_ = newElem;
    return *this;
}

template<typename T>
void SVector<T>::adjustCapacity(int n)
{
    auto newElem = new T[capacity_ = n];
    for (int i = 0; i < size_; ++i)
    {
        newElem[i] = elem_[i];
    }
    delete[] elem_;
    elem_ = newElem;
}

template<typename T>
void SVector<T>::check(bool isExpand)
{
    if (isExpand && size_ == capacity_)
    {
        adjustCapacity(size_ * 2);
        return;
    }
    if (!isExpand && kDefaultCapacity < capacity_ && size_ * 4 <= capacity_)
    {
        int n = capacity_ / 2 < kDefaultCapacity ? kDefaultCapacity : capacity_ / 2;
        adjustCapacity(n);
    }
}

template<typename T>
T SVector<T>::remove(SVector::Rank r)
{
    auto oldV = elem_[r];
    for (int i = r; i < size_ - 1; ++i)
    {
        elem_[i] = elem_[i + 1];
    }
    --size_;
    check(false);
    return oldV;
}

template<typename T>
int SVector<T>::remove(SVector::Rank lo, SVector::Rank hi)
{
    if (hi <= lo) return 0;
    while (hi < size_)
    {
        elem_[lo++] = elem_[hi++];
    }
    size_ = lo;
    check(false);
    return hi - lo;
}

template<typename T>
typename SVector<T>::Rank SVector<T>::insert(SVector::Rank r, const T &e)
{
    check(true);
    for (int i = size_; i > r; --i)
    {
        elem_[i] = elem_[i - 1];
    }
    elem_[r] = e;
    ++size_;
    return r;
}

template<typename T>
typename SVector<T>::Rank SVector<T>::insert(const T &e)
{
    return insert(size(), e);
}

template<typename T>
inline void swap(T &a, T &b) noexcept
{
    T tmp = b;
    b = a;
    a = tmp;
}

/*
 * bubbleSort A[lo, hi)
 */
template<typename T>
void bubbleSort_v1(T *A, int lo, int hi)
{
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int i = lo + 1; i < hi; ++i)
        {
            if (A[i] < A[i - 1])
            {
                swap(A[i - 1], A[i]);
                sorted = false;
            }
        }
        --hi;
    }
}

template<typename T>
void bubbleSort_v2(T *A, int lo, int hi)
{
    while (lo < hi)
    {
        int last = lo;
        for (int i = lo + 1; i < hi; ++i)
        {
            if (A[i] < A[i - 1])
            {
                last = i;
                swap(A[i], A[i - 1]);
            }
        }
        hi = last;
    }
}

/*
 * mergeSort A[lo, hi)
 */
template<typename T>
void merge(T *A, int lo, int mid, int hi)
{
    T *aux = new T[mid - lo];
    int t = 0;
    for (int i = lo; i < mid; ++i)
    {
        aux[t++] = A[i];
    }
    int i = 0, j = mid, k = lo;
    while (i < t && j < hi)
    {
//        the statement can guarantee the stability of the algorithm.
        if (aux[i] <= A[j]) A[k++] = aux[i++];
        else A[k++] = A[j++];
    }
    while (i < t) A[k++] = aux[i++];
    delete[] aux;
}

template<typename T>
void mergeSort(T *A, int lo, int hi)
{
    if (lo + 1 == hi) return;
    int mid = (lo + hi) / 2;
    mergeSort(A, lo, mid);
    mergeSort(A, mid, hi);
    merge(A, lo, mid, hi);
}

template<typename T>
void insertSort(T *A, int lo, int hi)
{
    T k;
    for (int i = lo + 1, j; i < hi; ++i)
    {
        k = A[i];
        for (j = i - 1; j >= lo && A[j] > k; --j)
        {
            A[j + 1] = A[j];
        }
        A[j + 1] = k;
    }
}


template<typename T>
void SVector<T>::sort(SVector::Rank lo, SVector::Rank hi)
{
    srand(time(nullptr));
    switch (rand() % 4)
    {
        case 0:
            bubbleSort_v1(elem_, lo, hi);
            break;
        case 1:
            bubbleSort_v2(elem_, lo, hi);
            break;
        case 2:
            mergeSort(elem_, lo, hi);
            break;
        case 3:
            insertSort(elem_, lo, hi);
            break;
    }
}

template<typename T>
void SVector<T>::sort()
{
    sort(0, size_);
}

template<typename T>
void SVector<T>::unsort(SVector::Rank lo, SVector::Rank hi)
{
    auto pA = elem_ + lo;
    for (int i = hi - lo; i > 0; --i)
    {
        swap(pA[i - 1], pA[rand() % i]);
    }
}

template<typename T>
void SVector<T>::unsort()
{
    unsort(0, size_);
}

template<typename T>
int SVector<T>::deduplicate()
{
    int oz = size_;
    Rank i = 1;
    while (i < size())
    {
        find(elem_[i], 0, i) != -1 ? remove(i) : ++i;
    }
    return oz - size_;
}

template<typename T>
int SVector<T>::uniquify()
{
    int i, j;
    for (i = 0, j = i; j < size_; ++j)
    {
        if (elem_[i] != elem_[j])
        {
            elem_[++i] = elem_[j];
        }
    }
    size_ = ++i;
    check(false);
    return j - i;
}

template<typename T>
void SVector<T>::traverse(void (*pFun)(T &))
{
    for (int i = 0; i < size(); ++i)
    {
        pFun(elem_[i]);
    }
}

template<typename T>
template<typename F>
void SVector<T>::traverse(F f)
{
    for (int i = 0; i < size(); ++i)
    {
        f(elem_[i]);
    }
}
}


#endif //TSINGHUA_DATASTRUCTURE_SVECTOR_H
