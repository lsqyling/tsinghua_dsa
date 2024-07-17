//
// Created by shiqing on 2019/8/11.
//

#include "../common/CommonHeaders.h"
#include "include/SortAlg.h"
#include <chrono>
#include <boost/test/unit_test.hpp>

constexpr int Len = 65535;

namespace page_303 {

/*
 * Question 2: Two-way bubble sort algorithm. A[lo, hi]
 */
template<typename T>
void twoWayBubbleSort(T *A, int lo, int hi)
{
    bool controlFlag = 1, flag = 1;
    int i, j;
    while (lo < hi)
    {
        if (controlFlag)
        {
            j = lo;
            while (j++ < hi)
            {
                if (A[j] < A[j - 1])
                {
                    SortAlg::swap(A[j], A[j - 1]);
                    flag = 0;
                }
            }
            if (flag) return;
            --hi;
            controlFlag = 0;
        }

        else
        {

            i = hi;
            while (lo < i--)
            {
                if (A[i + 1] < A[i])
                {
                    SortAlg::swap(A[i + 1], A[i]);
                    flag = 1;
                }
            }
            if (flag == 0) return;
            ++lo;
            controlFlag = 1;
        }
    }
}

/*
 * Question 3: partition by odd and even A[lo, hi]
 */
inline int getEvenPivot(int *A, int lo, int hi, int &flag)
{
    int j = lo;
    while (j <= hi && (A[j] & 1)) ++j;
    if (j > hi)
    {
        return flag = 1;
    }
    SortAlg::swap(A[j], A[lo]);
    return A[lo];
}

void partitionByEven(int *A, int lo, int hi)
{
    int flag = 0;
    int pivot = getEvenPivot(A, lo, hi, flag);
    if (flag) return;
    while (lo < hi)
    {
        while (lo < hi && A[hi] % 2 == 0) --hi;
        A[lo] = A[hi];
        while (lo < hi && A[lo] % 2 == 1) ++lo;
        A[hi] = A[lo];
    }
    A[lo] = pivot;
}

/*
 * Question 4: random partition
 */
void partitionRandom(int *A, int lo, int hi)
{
    static std::default_random_engine e;
    static std::uniform_int_distribution<int> u(lo, hi);
    SortAlg::swap(A[lo], A[u(e)]);
    int pivot = A[lo];
    while (lo < hi)
    {
        while (lo < hi && pivot <= A[hi]) --hi;
        A[lo] = A[hi];
        while (lo < hi && A[lo] <= pivot) ++lo;
        A[hi] = A[lo];
    }
    A[lo] = pivot;
}

/*
 * Question 5: find the kth smallest number in the array.
 */
int partitionIndex(int *A, int lo, int hi)
{
    int pivot = A[lo];
    while (lo < hi)
    {
        while (lo < hi && pivot <= A[hi]) --hi;
        A[lo] = A[hi];
        while (lo < hi && A[lo] <= pivot) ++lo;
        A[hi] = A[lo];
    }
    A[lo] = pivot;
    return lo;
}

int findKthSmallestNumber(int *A, int n, int k)
{
    if (n < k) throw std::invalid_argument("arguments is error");
    int lo = 0, hi = n - 1;
    int index = partitionIndex(A, lo, hi);
    while (index != k - 1)
    {
        if (k - 1 < index)
        {
            hi = index - 1;
            index = partitionIndex(A, lo, hi);
        }
        else
        {
            lo = index + 1;
            index = partitionIndex(A, lo, hi);
        }
    }
    return A[index];
}

/*
 * Question 6: partitionByMinAbsN1_N2AndMinAbsS1_S2
 */

inline int sum(int *A, int left, int right) noexcept
{
    int s = 0;
    for (int i = left; i <= right; ++i)
    {
        s += A[i];
    }
    return s;
}

int partitionByMinAbsN1_N2AndMinAbsS1_S2(int *A, int n)
{
    assert(2 <= n);
    int lo = 0, hi = n - 1;
    int index = partitionIndex(A, lo, hi);
    int k = n / 2;
    while (index != k)
    {
        if (k < index)
        {
            hi = index - 1;
            index = partitionIndex(A, lo, hi);
        }
        else
        {
            lo = index + 1;
            index = partitionIndex(A, lo, hi);
        }
    }

    int n1, n2, s1 = 0, s2 = 0;

    if (n % 2 == 0)
    {
        while (0 < k && A[k - 1] == A[k]) --k;
        if (k < n / 2 || (k == n / 2 && A[k + 1] == A[k]))
        {
            n1 = k;
            n2 = n - n1;
            s1 = sum(A, 0, k - 1);
            s2 = sum(A, k, n - 1);
        }
        else
        {
            n1 = n2 = n / 2;
            s1 = sum(A, 0, k);
            s2 = sum(A, k + 1, n - 1);
        }
    }
    else
    {
        while (0 < k && A[k - 1] == A[k]) --k;
        n1 = k;
        n2 = n - n1;
        s1 = sum(A, 0, k - 1);
        s2 = sum(A, k, n - 1);
    }

    cout << "|n1 - n2| = " << std::abs(n1 - n2) << endl;
    cout << "|s1 - s2| = " << std::abs(s1 - s2) << endl;

    return k;

}

/*
 * Question 7: Dutch national flag
 */
enum class FlagColor
{
    Red, White, Blue
};

std::ostream &operator<<(std::ostream &os, const FlagColor &color)
{
    switch (color)
    {
        case FlagColor::Red:
            os << std::string("Red");
            break;
        case FlagColor::White:
            os << std::string("White");
            break;
        case FlagColor::Blue:
            os << std::string("Blue");
    }
    return os;
}

void dutchNationalFlagSort(FlagColor *A, int lo, int hi)
{
    if (hi <= lo) return;
    int lt = lo, i = lo + 1, gt = hi;
    auto pivot = A[lo];

    while (i <= gt)
    {
        if (A[i] < pivot)
        {
            SortAlg::swap(A[lt], A[i]);
            ++lt;
            ++i;
        }
        else if (pivot < A[i])
        {
            SortAlg::swap(A[i], A[gt]);
            --gt;
        }
        else
        {
            ++i;
        }
    }

    dutchNationalFlagSort(A, lo, lt - 1);
    dutchNationalFlagSort(A, gt + 1, hi);
}

void dutchNationalFlagQuickSort(FlagColor *A, int lo, int hi)
{
    int lt = lo, j = lo, gt = hi;
    while (j <= gt)
    {
        switch (A[j])
        {
            case FlagColor::Red:
                SortAlg::swap(A[lt], A[j]);
                ++lt;
                ++j;
                break;
            case FlagColor::White:
                ++j;
                break;
            case FlagColor::Blue:
                SortAlg::swap(A[j], A[gt]);
                --gt;
        }
    }
}

FlagColor colors[] = {FlagColor::Red, FlagColor::White, FlagColor::Blue};

FlagColor *createRandomArray(int n)
{
    static std::default_random_engine e;
    static std::uniform_int_distribution<int> u(0, 2);
    auto A = new FlagColor[n];
    for (int i = 0; i < n; ++i)
    {
        A[i] = colors[u(e)];
    }
    return A;
}

}

namespace page_314 {

template<typename T>
struct ForwardNode
{

    template<typename... Args>
    ForwardNode(Args &&... params) : data_(std::forward<Args>(params)...), next_(nullptr)
    {
        static_assert(
                std::is_constructible<T, Args...>::value,
                "Parameter args... can't be used to construct a T"
        );
    }

    T data_;
    ForwardNode *next_;
};

template<typename T> using Node = ForwardNode<T>;

Node<int> *createRandomIntegerList(int n)
{
    static std::default_random_engine e;
    static std::uniform_int_distribution<int> u(0, 0x7fff);
    Node<int> *root_ = new Node<int>, *p;
    for (int i = 0; i < n; ++i)
    {
        p = new Node<int>(u(e));
        p->next_ = root_->next_;
        root_->next_ = p;
    }
    return root_;
}

template<typename T>
void destroyList(Node<T> *List)
{
    Node<T> *p = List, *q;
    while (p)
    {
        q = p->next_;
        delete p;
        p = q;
    }
}

template<typename T>
bool isSorted(Node<T> *List)
{
    if (List->next_ == nullptr || List->next_->next_ == nullptr)
    {
        return true;
    }
    Node<T> *p = List->next_;
    while (p->next_ && p->data_ <= p->next_->data_) p = p->next_;
    return p->next_ == nullptr;
}

template<typename T>
std::ostream &printList(std::ostream &os, Node<T> *List)
{
    auto p = List->next_;
    os << "[";
    while (p)
    {
        cout << p->data_ << " ";
        p = p->next_;
    }
    os << "]";
    return os;
}

/*
 * Question 4: select sort on List
 */
template<typename T>
void selectSortOnList(Node<T> *List)
{
    if (List->next_ == nullptr || List->next_->next_ == nullptr) return;
    Node<T> *h1 = List, *h2 = new Node<T>, *preH2 = nullptr;
    h2->next_ = h1->next_;
    h1->next_ = h2;

    Node<T> *p, *preMax;
    bool flag = true;
    do
    {
        preMax = p = h2;
        while (p->next_)
        {
            if (preMax->next_->data_ < p->next_->data_)
            {
                preMax = p;
            }
            p = p->next_;
        }

        if (preMax->next_)
        {
            p = preMax->next_;
            preMax->next_ = p->next_;

            p->next_ = h1->next_;
            h1->next_ = p;
            if (flag)
            {
                preH2 = p;
                flag = false;
            }
        }
        else
        {
            preH2->next_ = nullptr;
            p = nullptr;
            delete h2;
        }

    } while (p);

}

/*
 * Question 5: is it a small root pile
 * A[0 1 2 ...n]
 */
bool isSmallRootPile(const int *A, int n)
{
    if (n < 2) return true;
    int i;
    for (i = 1; i < n / 2;)
    {
        if (A[i] <= A[2 * i] && A[i] <= A[2 * i + 1])
        {
            ++i;
        }
        else break;
    }
    if (i < n / 2) return false;
    else
    {
        if (n % 2 == 1)
        {
            return A[i] <= A[2 * i] && A[i] <= A[2 * i + 1];
        }
        else
        {
            return A[i] <= A[2 * i];
        }
    }
}

}

namespace page_327 {
/*
 * Question 2: sort the A[ 0 1 2...m m + 1, ...m + n]
 */
void sortByMergeMAndN(int *A, int m, int n)
{
    if (m == 0 || n == 0) return;
    auto aux = new int[m + n + 1];
    for (int i = 1; i <= m + n; ++i)
    {
        aux[i] = A[i];
    }

    int i, j, k;

    for (i = k = 1, j = m + 1; i <= m && j <= m + n;)
    {
        if (aux[i] <= aux[j])
        {
            A[k++] = aux[i++];
        }
        else A[k++] = aux[j++];
    }

    if (i == m + 1)
    {
        delete[] aux;
        return;
    }
    while (j == m + n + 1 && i <= m)
    {
        A[k++] = aux[j++];
    }
    delete[] aux;
}

/*
 * Question 3: count sorting
 * n, the number of A
 */
void countSort(const int *A, int *B, int n)
{
    int cnt;
    for (int i = 0; i < n; ++i)
    {
        cnt = 0;
        for (int j = 0; j < n; ++j)
        {
            if (A[j] < A[i])
            {
                ++cnt;
            }
        }
        B[cnt] = A[i];
    }
}

}

BOOST_AUTO_TEST_SUITE(page_327)

BOOST_AUTO_TEST_CASE(sortByMergeMAndN_)
{
    int A[] = {0, 2, 3, 4, 5, 0, 1, 6, 7};
    page_327::sortByMergeMAndN(A, 4, 4);
    BOOST_TEST(SortAlg::isSorted(A, 1, 9) == 1);
    printArray(cout, A) << endl;

    int A1[] = {0, 1, 2, 3, 5, 6, 7};
    page_327::sortByMergeMAndN(A1, 0, 6);
    BOOST_TEST(SortAlg::isSorted(A1, 1, 7) == 1);
    printArray(cout, A1) << endl;

    int A2[] = {0, 1, 2, 3, 5, 6, 7};
    page_327::sortByMergeMAndN(A2, 6, 0);
    BOOST_TEST(SortAlg::isSorted(A2, 1, 7) == 1);
    printArray(cout, A2) << endl;

    int A3[] = {0, 1, 2, 3, 4, -1, 0, 0, 5, 7, 8, 9, 10};
    page_327::sortByMergeMAndN(A3, 4, 8);
    BOOST_TEST(SortAlg::isSorted(A3, 1, 13) == 1);
    printArray(cout, A3) << endl;

}

BOOST_AUTO_TEST_CASE(countSort_)
{
    int A[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int B[10];
    page_327::countSort(A, B, 10);
    BOOST_TEST(SortAlg::isSorted(B, 0, 10));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(page_314)

BOOST_AUTO_TEST_CASE(selectSortOnList_)
{
    Node<int> *List = page_314::createRandomIntegerList(Len);
    auto t3 = std::chrono::system_clock::now();
    page_314::selectSortOnList(List);
    auto t4 = std::chrono::system_clock::now();
    cout << "select sort on List cost ( "
         << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count()
         << " ) milliseconds\n";

    BOOST_TEST(page_314::isSorted(List) == 1);
    page_314::destroyList(List);

}

BOOST_AUTO_TEST_CASE(isSmallRootPile_)
{
    int A[] = {0, 19, 34, 26, 97, 56, 75};
    BOOST_TEST(page_314::isSmallRootPile(A, 6) == 1);
    int A1[] = {0, 19, 75, 34, 26, 97, 56};
    BOOST_TEST(page_314::isSmallRootPile(A1, 6) == 0);

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(page_303)

BOOST_AUTO_TEST_CASE(dutchNationalFlagSort_)
{
    auto A = page_303::createRandomArray(Len);
    auto t3 = std::chrono::system_clock::now();
    page_303::dutchNationalFlagSort(A, 0, Len - 1);
    auto t4 = std::chrono::system_clock::now();
    cout << "dutch national flag sort cost ( "
         << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count()
         << " ) milliseconds\n";

    BOOST_TEST(SortAlg::isSorted(A, 0, Len) == 1);

    delete[] A;

    auto array = page_303::createRandomArray(Len);
    auto t1 = std::chrono::system_clock::now();
    page_303::dutchNationalFlagQuickSort(array, 0, Len - 1);
    auto t2 = std::chrono::system_clock::now();
    cout << "dutch national flag quick sort cost ( "
         << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
         << " ) milliseconds\n";
    BOOST_TEST(SortAlg::isSorted(array, 0, Len) == 1);

    delete[] array;

}

BOOST_AUTO_TEST_CASE(partitionByMinAbsN1_N2AndMinAbsS1_S2_)
{
    int A[] = {4, 2, 4, 4, 3, 5, 0, 1, 3};
    auto k = page_303::partitionByMinAbsN1_N2AndMinAbsS1_S2(A, 9);
    printArray(cout, A) << ", k = " << k << endl;
    cout << "--------------------" << endl;
    int A1[] = {2, 2, 2, 2, 2, 2};
    k = page_303::partitionByMinAbsN1_N2AndMinAbsS1_S2(A1, 6);
    printArray(cout, A1) << ", k = " << k << endl;
}

BOOST_AUTO_TEST_CASE(partition_)
{
    int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int A1[] = {0, 2, 4, 6, 8};
    int A2[] = {1, 3, 5, 7, 9};

    page_303::partitionByEven(A, 0, 9);
    printArray(cout, A);
    printArray(cout, A1);
    printArray(cout, A2);

    page_303::partitionRandom(A, 0, 9);
    printArray(cout, A);
}

BOOST_AUTO_TEST_CASE(findKthSmallestNumber_)
{
    int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int A1[] = {8, 6, 4, 2, 0};
    int A2[] = {1, 4, 2, 5, 0, 8, 9, 3};

    auto r = page_303::findKthSmallestNumber(A, 10, 5);
    BOOST_TEST(r == 4);
    r = page_303::findKthSmallestNumber(A1, 5, 2);
    BOOST_TEST(r == 2);
    r = page_303::findKthSmallestNumber(A2, 8, 4);
    BOOST_TEST(r == 3);

}

BOOST_AUTO_TEST_CASE(twoWayBubbleSort_)
{

    int *A = SortAlg::createRandomArray(Len);
    auto t3 = std::chrono::system_clock::now();
    page_303::twoWayBubbleSort(A, 0, Len - 1);
    auto t4 = std::chrono::system_clock::now();
    cout << "two-way bubble sort cost ( "
         << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count()
         << " ) milliseconds\n";

    BOOST_TEST(SortAlg::isSorted(A, 0, Len) == 1);

    delete[] A;

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(my_testsuite)

BOOST_AUTO_TEST_CASE(findXMoreThanHalf)
{
    int array[] = {1, 2, 2, 1, 3, 2, 2};
    BOOST_TEST(SortAlg::findXMoreThanHalf(array, 7) == 2);
}

BOOST_AUTO_TEST_CASE(bubbleSort)
{
    int *array = SortAlg::createRandomArray(Len);
    auto t1 = std::chrono::system_clock::now();
    SortAlg::bubbleSort(array, 0, Len);
    auto t2 = std::chrono::system_clock::now();
    cout << "bubble sort cost ( "
         << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
         << " ) milliseconds\n";
    BOOST_TEST(SortAlg::isSorted(array, 0, Len) == 1);
    delete[] array;

}

BOOST_AUTO_TEST_CASE(insertSort)
{
    int *array = SortAlg::createRandomArray(Len);
    auto t1 = std::chrono::system_clock::now();
    SortAlg::insertSort(array, 0, Len);
    auto t2 = std::chrono::system_clock::now();
    cout << "insert sort cost ( "
         << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
         << " ) milliseconds\n";
    BOOST_TEST(SortAlg::isSorted(array, 0, Len) == 1);

    delete[] array;

    int *A = SortAlg::createRandomArray(Len);
    auto t3 = std::chrono::system_clock::now();
    SortAlg::binaryInsertSort(A, 0, Len);
    auto t4 = std::chrono::system_clock::now();
    cout << "binary insert sort cost ( "
         << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count()
         << " ) milliseconds\n";

    BOOST_TEST(SortAlg::isSorted(A, 0, Len) == 1);

    delete[] A;

}

BOOST_AUTO_TEST_CASE(shellShort)
{
    int *A = SortAlg::createRandomArray(Len);
    auto t3 = std::chrono::system_clock::now();
    SortAlg::shellShort(A, 0, Len);
    auto t4 = std::chrono::system_clock::now();
    cout << "shell sort cost ( "
         << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count()
         << " ) milliseconds\n";

    BOOST_TEST(SortAlg::isSorted(A, 0, Len) == 1);

    delete[] A;

}

BOOST_AUTO_TEST_CASE(quickSort)
{
    int *A = SortAlg::createRandomArray(Len);
    auto t3 = std::chrono::system_clock::now();
    SortAlg::quickSort(A, 0, Len - 1);
    auto t4 = std::chrono::system_clock::now();
    cout << "quick insert sort cost ( "
         << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count()
         << " ) milliseconds\n";
    BOOST_TEST(SortAlg::isSorted(A, 0, Len) == 1);

    delete[] A;
}

BOOST_AUTO_TEST_CASE(selectSort)
{
    int *A = SortAlg::createRandomArray(Len);
    auto t3 = std::chrono::system_clock::now();
    SortAlg::selectSort(A, 0, Len);
    auto t4 = std::chrono::system_clock::now();
    cout << "select insert sort cost ( "
         << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count()
         << " ) milliseconds\n";
    BOOST_TEST(SortAlg::isSorted(A, 0, Len) == 1);

    delete[] A;
}

BOOST_AUTO_TEST_CASE(heapSort)
{
    int *A = SortAlg::createRandomArray(Len + 1);
    auto t3 = std::chrono::system_clock::now();
    SortAlg::heapSort(A, Len);
    auto t4 = std::chrono::system_clock::now();
    cout << "heap sort cost ( "
         << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count()
         << " ) milliseconds\n";
    BOOST_TEST(SortAlg::isSorted(A, 1, Len + 1) == 1);

    delete[] A;
}

BOOST_AUTO_TEST_SUITE_END()





