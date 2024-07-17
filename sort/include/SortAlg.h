//
// Created by shiqing on 2019/8/11.
//

#ifndef TSINGHUA_DATASTRUCTURE_SORTALG_H
#define TSINGHUA_DATASTRUCTURE_SORTALG_H

namespace SortAlg {

int *createRandomArray(int n)
{
    static std::default_random_engine e(n >> 1);
    static std::uniform_int_distribution<int> u(0, 0x7fff);
    int *A = new int[n];
    for (int i = 0; i < n; ++i)
    {
        A[i] = u(e);
    }
    return A;
}

template<typename T>
T findXMoreThanHalf(const T *A, int n) noexcept
{
    int j = 0, cnt = 1;
    for (int i = 1; i < n; ++i)
    {
        if (A[j] == A[i])
        {
            ++cnt;
        }
        else if (--cnt == 0)
        {
            j = i;
            cnt = 1;
        }
    }
    return A[j];
}

template<typename T>
inline void swap(T &a, T &b) noexcept
{
    T tmp = b;
    b = a;
    a = tmp;
}

template<typename T>
inline bool isSorted(T *A, int lo, int hi) noexcept
{
    while (++lo < hi && A[lo - 1] <= A[lo]);
    return lo == hi;
}

/*
 * sorting A[lo, hi)
 */
template<typename T>
void bubbleSort(T *A, int lo, int hi) noexcept
{
    bool flag = true;
    for (; lo < hi && flag; --hi)
    {
        flag = false;
        int i = lo;
        while (++i < hi)
        {
            if (A[i] < A[i - 1])
            {
                swap(A[i], A[i - 1]);
                flag = true;
            }
        }
    }
}

/*
 * insert sort[lo, hi)
 */
template<typename T>
void insertSort(T *A, int lo, int hi) noexcept
{
    T k;
    int j;
    for (int i = lo + 1; i < hi; ++i)
    {
        k = A[i];
        for (j = i - 1; j >= lo && k < A[j]; --j)
        {
            A[j + 1] = A[j];
        }
        A[j + 1] = k;
    }
}

/*
 * binary insert sort[lo, hi)
 */
template<typename T>
void binaryInsertSort(T *A, int lo, int hi) noexcept
{
    T k;
    int l, h, mid;
    for (int i = lo + 1; i < hi; ++i)
    {
        k = A[i];
//            binary search in [lo, i)
        l = lo, h = i;
        while (l < h)
        {
            mid = (l + h) / 2;
            if (k < A[mid]) h = mid;
            else l = mid + 1;
        }

        for (int j = i - 1; j >= h; --j)
        {
            A[j + 1] = A[j];
        }
        A[h] = k;
    }
}

/*
 * shell short
 */
template<typename T>
void shellShort(T *A, int lo, int hi) noexcept
{
    int h = 1;
    while (h < (hi - lo) / 3) h = 3 * h + 1;

    T k;
    int j;
    while (1 <= h)
    {
        for (int i = lo + h; i < hi; ++i)
        {
            k = A[i];
            for (j = i - h; k < A[j] && j >= lo; j -= h)
            {
                A[j + h] = A[j];
            }
            A[j + h] = k;
        }

        h /= 3;
    }
}

/*
 * quick sort
 */
template<typename T>
inline T median3(T *A, int left, int right) noexcept
{
    int mid = (left + right) / 2;
    if (A[mid] < A[left])
    {
        swap(A[mid], A[left]);
    }
    if (A[right] < A[left])
    {
        swap(A[right], A[left]);
    }
    if (A[right] < A[mid])
    {
        swap(A[mid], A[right]);
    }
    swap(A[mid], A[right - 1]);
    return A[right - 1];
}

constexpr int cutOff = 50;

template<typename T>
void quickSort(T *A, int left, int right) noexcept
{
    if (cutOff < right - left)
    {
        auto pivot = median3(A, left, right);
        int i = left, j = right - 1;
        for (;;)
        {
            while (A[++i] < pivot);
            while (pivot < A[--j]);

            if (i < j)
            {
                swap(A[i], A[j]);
            }
            else break;
        }
        swap(A[i], A[right - 1]);
        quickSort(A, left, i - 1);
        quickSort(A, i + 1, right);
    }
    else
    {
        insertSort(A, left, right + 1);
    }

}

int partition(int A[], int left, int right)
{
    int pivot = A[right];
    int i = left - 1, j;
    for (j = left; j < right; ++j)
    {
        if (A[j] <= pivot)
        {
            ++i;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[right]);
    return i + 1;
}


void quickSort(int A[], int left, int right)
{
    if (left < right)
    {
        int q = partition(A, left, right);
        quickSort(A, left, q - 1);
        quickSort(A, q + 1, right);
    }
}


template<typename T>
void selectSort(T *A, int lo, int hi)
{
    T min;
    int i;
    while (++lo < hi)
    {
        min = A[lo - 1];
        for (i = lo; i < hi; ++i)
        {
            if (A[i] < min) min = A[i];
        }
        swap(A[lo - 1], min);
    }
}

template<typename T>
void adjustUp(T *A, int k) noexcept
{
    A[0] = A[k];
    int i = k / 2;
    while (0 < i && A[i] < A[0])
    {
        A[k] = A[i];
        k = i;
        i /= 2;
    }
    A[k] = A[0];
}

template<typename T>
void adjustDown(T *A, int k, int len) noexcept
{
    A[0] = A[k];
    for (int i = 2 * k; i <= len; i *= 2)
    {
        if (i < len && A[i] < A[i + 1])
        {
            ++i;
        }
        if (A[i] <= A[0]) break;
        else
        {
            A[k] = A[i];
            k = i;
        }
    }
    A[k] = A[0];
}

template<typename T>
void buildMaxHeap(T *A, int n) noexcept
{
    for (int i = n / 2; 0 < i; --i)
    {
        adjustDown(A, i, n);
    }

}

/*
 * heap sort A[0 1 2...n]
 */
template<typename T>
void heapSort(T *A, int n)
{
    buildMaxHeap(A, n);
    for (int i = n; i > 1; --i)
    {
        swap(A[i], A[1]);
        adjustDown(A, 1, i - 1);
    }
}

}

#endif //TSINGHUA_DATASTRUCTURE_SORTALG_H
