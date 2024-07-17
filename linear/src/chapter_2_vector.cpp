//
// Created by shiqing on 2020/5/9.
//
#include <SVector.h>
#include <Fib.h>
#include "../../common/CommonHeaders.h"

namespace binary_search {

/*
 * Search X in strictly increasing sequence A[lo, hi) ----> A[0, n)
 */
int binarySearch_v1(int A[], int lo, int hi, int x)
{
    int mid;
    while (lo < hi)
    {
        mid = (lo + hi) / 2;
        if (x == A[mid]) return mid;
        else if (x < A[mid]) hi = mid;
        else lo = mid + 1;
    }
    return -1;
}

/*
 * search x in strictly increasing sequence A[lo, hi) ----> A[0, n)
 */
int fibonacciSearch(int A[], int lo, int hi, int x)
{
    Fib fib(hi - lo);
    while (lo < hi)
    {
        while (hi - lo < fib.get()) fib.pre();
        auto mid = lo + fib.get() - 1;
        if (x < A[mid]) hi = mid;
        else if (A[mid] < x) lo = mid + 1;
        else return mid;
    }
    return -1;
}


/*
 * Search the first position greater than or equal to x in increasing sequence
 * A[left, right] ---->A[0, n]
 */
int lower_bound(int A[], int left, int right, int x)
{
    int mid;
    while (left < right)
    {
        mid = (left + right) / 2;
        x <= A[mid] ? right = mid : left = mid + 1;
    }
    return left;
}

/*
 * Search the first position greater than x in increasing sequence A[left, right] ---->A[0, n]
 */
int upper_bound(int A[], int left, int right, int x)
{
    int mid;
    while (left < right)
    {
        mid = (left + right) / 2;
        x < A[mid] ? right = mid : left = mid + 1;
    }
    return left;
}

void testingSearch()
{
    int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22};
    for (const auto &a : A)
    {
        cout << fibonacciSearch(A, 0, 23, a) << " ";
    }
    cout << fibonacciSearch(A, 0, 23, 25) << endl;
}
}

namespace svector_test {
using namespace linear;

void testingConstructor()
{
    SVector<int> s1, s2(10, 5, 3);
    cout << s1 << endl;
    cout << s2 << endl;
    float A[] = {1.0f, 2.0f, 3.0f, 4.0f};
    SVector<float> s3(A, 4);
    cout << s3 << endl;
    SVector<float> s4(A, 1, 4);
    cout << s4 << endl;
    SVector<int> s5(s2);
    s1 = s5;
    cout << s1 << endl;
    cout << s5 << endl;
    SVector<int> s6(s2, 1, 4);
    cout << s6 << endl;
}

void testingReadableInterface()
{
    int A[] = {0, 1, 4, 2, 1, 0, 5, 6, 10, 9, 5, 2, 8, 7, 2};

    SVector<int> s1(A, 15);
    cout << s1.size() << endl;
    cout << s1.empty() << endl;
    cout << s1.disordered() << endl;
    cout << s1.find(6) << endl;
    s1.sort();
    cout << s1.search(2) << endl;
    cout << s1 << endl;
    cout << s1[1] << endl;
    const SVector<int> s2(s1);
    cout << s2[1] << endl;
}

void testingWritableInterface()
{
    int A[] = {0, 1, 4, 2, 1, 0, 5, 6, 10, 9, 5, 2, 8, 7, 2};
    SVector<int> s1(A, 15);
    cout << s1 << endl;
    s1.remove(0);
    s1.remove(1, 3);
    cout << s1 << endl;
    s1.remove(1, 1);
    cout << s1 << endl;
    s1.sort();
    cout << s1 << endl;
    s1.unsort();
    cout << s1 << endl;
    s1.deduplicate();
    cout << s1 << endl;

    SVector<int> s2(A, 15);
    s2.sort();
    cout << s2 << endl;
    s2.uniquify();
    cout << s2 << endl;
    SVector<int> s3;
    for (int i = 0; i < 20; ++i)
    {
        s3.insert(i);
    }
    cout << s3 << endl;
}

template<typename T>
void addDouble(T &val)
{
    val *= 2;
}

void testingTraversal()
{
    int A[] = {0, 1, 4, 2, 1, 0, 5, 6, 10, 9, 5, 2, 8, 7, 2};
    SVector<int> s1(A, 15);
    s1.traverse(addDouble);
    cout << s1 << endl;
    s1.traverse([](int a)
                { cout << a << " "; });
    cout << endl;
    s1.traverse([](auto &x)
                { return x /= 2; });
    cout << s1 << endl;
    bubbleSort_v1(A, 0, 15);
    printArray(cout, A) << endl;
    shuffle(A);
    printArray(cout, A) << endl;
    s1.sort();
    cout << s1 << endl;
    s1.uniquify();
    cout << s1 << endl;
    s1.unsort();
    cout << s1 << endl;
}

void testingExpansion()
{
    SVector<int> si;
    for (int i = 0; i < 0xfffff; ++i)
    {
        si.insert(i);
    }
    for (int j = 0; j < 0xfffff; ++j)
    {
        si.remove(si.size() - 1);
    }
}

void testingBubbleSortInVector()
{
    auto &A = generateRandomArray<0xffff>();
    calledCostTime(bubbleSort_v2<int>, "bubbleSort_v2", A, 0, 0xffff);

    int B[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    bubbleSort_v2(B, 0, 10);
    printArray(cout, B) << endl;

}

void testingMergeSort()
{
    int A[] = {9, 8, 7, 6, 5, 4, 3, 3, 2, 1, 0};
    mergeSort(A, 0, 11);
    printArray(cout, A) << endl;
    auto &p1 = generateRandomArray<0xffff>();
    calledCostTime(bubbleSort_v1<int>, "bubble_v1", p1, 0, 0xffff);
    assert(isSorted(p1));
    shuffle(p1);
    calledCostTime(mergeSort<int>, "mergeSort", p1, 0, 0xffff);
    assert(isSorted(p1));
}

void testingInsertSort()
{
    int A[] = {9, 8, 7, 6, 5, 4, 3, 3, 2, 1, 0};
    insertSort(A, 0, 11);
    printArray(cout, A) << endl;
    auto &p1 = generateRandomArray<0xffff>();
    calledCostTime(insertSort<int>, "insertSort", p1, 0, 0xffff);
    assert(isSorted(p1));
    shuffle(p1);
    calledCostTime(insertSort<int>, "insertSort", p1, 0, 0xffff);
    assert(isSorted(p1));
}
}


int main(int argc, char *argv[])
{
    svector_test::testingConstructor();
    svector_test::testingReadableInterface();
    svector_test::testingWritableInterface();
    svector_test::testingTraversal();
    svector_test::testingExpansion();
    svector_test::testingBubbleSortInVector();
    binary_search::testingSearch();
    svector_test::testingMergeSort();
    svector_test::testingInsertSort();
    return 0;
}
