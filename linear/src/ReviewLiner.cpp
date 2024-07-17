//
// Created by shiqing on 19-7-16.
//
#include <functional>
#include "../../common/CommonHeaders.h"
#include "../include/Josephus.h"
#include "../include/Stack.h"
#include "../include/Queue.h"

namespace josephus {
constexpr int Len = 100;
int Q[Len];
int head_, tail_, size_;

void enqueue(int x)
{
    if (size_ == 0)
    {
        head_ = tail_ = 0;
        Q[0] = x;
    }
    else
    {
        tail_ = (tail_ + 1) % Len;
        Q[tail_] = x;
    }
    ++size_;
}

int dequeue()
{
    int z = Q[head_];
    head_ = (head_ + 1) % Len;
    --size_;
    return z;
}

void solve()
{
    int n, answer;
    printf("Enter an integer (1 --- 99):");
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        enqueue(i);
    }

    for (int j = 1; j < n; ++j)
    {
        int x = dequeue();
        dequeue();
        enqueue(x);
    }
    answer = Q[head_];
    printf("The value of Josephus(%d) is: %d\n", n, answer);
}
}

namespace linearList {
namespace sequentialList {
/*
 * chapter 2 linearList Page18. 1 --- 13;
 */
template<typename ElemType>
struct SequentialList
{
    explicit SequentialList(int n) : pData_(new ElemType[n]), size_(n), cap_(n)
    {
    }

    SequentialList(std::initializer_list<ElemType> li);

    SequentialList(const SequentialList &rhs);

    SequentialList &operator=(const SequentialList &) = delete;

    ~SequentialList()
    {
        delete[] pData_;
    }

    bool empty() const noexcept
    {
        return size_ == 0;
    }

    int size() const noexcept
    {
        return size_;
    }

    int capacity() const noexcept
    {
        return cap_;
    }

    ElemType &operator[](int index);

    ElemType operator[](int index) const;

public:
    ElemType *pData_;
    int size_, cap_;
};

template<typename T> using SeqList = SequentialList<T>;

template<typename T>
std::ostream &operator<<(std::ostream &os, const SequentialList<T> &rhs)
{
    os << '[';
    for (int i = 0; i < rhs.size_; ++i)
    {
        if (i != rhs.size_ - 1) os << rhs.pData_[i] << " ";
        else os << rhs.pData_[i];
    }
    os << ']';
    return os;
}

template<typename ElemType>
SequentialList<ElemType>::SequentialList(std::initializer_list<ElemType> li)
        : pData_(new int[li.size() * 2]),
          size_(li.size()), cap_(li.size() * 2)
{
    int index = 0;
    for (const auto &item : li)
    {
        pData_[index] = item;
        ++index;
    }
}

template<typename ElemType>
ElemType &SequentialList<ElemType>::operator[](int index)
{
    return pData_[index];
}

template<typename ElemType>
ElemType SequentialList<ElemType>::operator[](int index) const
{
    return pData_[index];
}

template<typename ElemType>
SequentialList<ElemType>::SequentialList(const SequentialList &rhs)
        : pData_(new ElemType[rhs.size()]), size_(rhs.size()), cap_(rhs.cap_)
{
    for (int i = 0; i < rhs.size(); ++i)
    {
        pData_[i] = rhs[i];
    }
}


/*void testing() {
    SequentialList<int> sli;
    cout << sli.size() << endl;
    cout << sli << endl;
    cout << sli.empty() << endl;

    SequentialList<int> s{0, 1, 2, 3, 4};
    cout << s.size() << endl;
    cout << s << endl;
    cout << s.empty() << endl;
    cout << s[3] << endl;

}*/

/*
 * question 1. delete min number
 */
template<typename T>
bool deleteMin(SeqList<T> &qL, T &toDelValue)
{
    if (qL.empty())
    {
        printf("The Sequential List is empty");
        return false;
    }
    int minIndex = 0;
    for (int i = 1; i < qL.size(); ++i)
    {
        if (qL[i] < qL[minIndex])
        {
            minIndex = i;
        }
    }
    toDelValue = qL[minIndex];
    qL[minIndex] = qL[qL.size() - 1];
    --qL.size_;
    return true;
}

void testingExerciseDelMin()
{
    SeqList<int> li{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int dVal;
    cout << deleteMin(li, dVal) << ", dVal = " << dVal << endl;
    cout << li << endl;
}

/*
 * question 2. reverse
 */
template<typename T>
void reverse(SeqList<T> &qL)
{
    for (int i = 0, j = qL.size() - 1; i < j; ++i, --j)
    {
        std::swap(qL[i], qL[j]);
    }
}

void testingReverse()
{
    SeqList<int> qL{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    reverse(qL);
    cout << qL << endl;
}

/*
 * question 3. delete the given value
 */
template<typename T>
void deleteX(SeqList<T> &qL, const T &x)
{
    int i = 0, j;
    while (qL[i] != x && i < qL.size()) ++i;
    if (i == qL.size()) return;
    j = i;
    while (++i < qL.size())
    {
        if (qL[i] != x)
        {
            qL[j] = qL[i];
            ++j;
        }
    }
    qL.size_ = j;
}

void testingDelX()
{
    SeqList<int> qL{1, 2, 3, 7, 4, 5, 7, 7, 7, 6, 7, 9};
    deleteX(qL, 7);
    cout << qL << endl;
}

template<typename T>
inline bool isRangeOf(SeqList<T> &qL, int index, T b, T e)
{
    return b <= qL[index] && qL[index] <= e;
}

/*
 * question 4 - 5. delete the range of value.
 */
template<typename T>
void deleteRange(SeqList<T> &qL, T b, T e)
{
    if (b > e)
    {
        printf("The range is illogical.");
        return;
    }
    int i = 0, j;
    while (!isRangeOf(qL, i, b, e) && i < qL.size()) ++i;
    j = i;
    while (++i < qL.size())
    {
        if (!isRangeOf(qL, i, b, e))
        {
            qL[j] = qL[i];
            ++j;
        }
    }
    qL.size_ = j;
}

void testingDeleteRange()
{
    SeqList<int> qL{1, 2, 3, 7, 4, 5, 7, 7, 7, 6, 7, 8};
    deleteRange(qL, 2, 4);
    cout << qL << endl;
}

/*
 * question 6. delete the repeats
 */
template<typename T>
void deleteRepeats(SeqList<T> &qL)
{
    if (qL.size() < 2) return;
    int i = 0, j = 0;
    while (++j < qL.size())
    {
        if (qL[i] != qL[j])
        {
            qL[++i] = qL[j];
        }
    }
    qL.size_ = i + 1;
}

void testingDeleteRepeats()
{
    SeqList<int> qL{0, 1, 1, 2, 3, 3, 4, 5, 5, 6, 6, 7, 8, 9};
    deleteRepeats(qL);
    cout << qL << endl;
}

/*
 * question 7. merge list
 */
template<typename T>
SeqList<T> mergeList(const SeqList<T> &lhs, const SeqList<T> &rhs)
{
    SeqList<T> r(rhs.size() + lhs.size());
    int i, j, k = 0;
    for (i = 0, j = 0; i < lhs.size() && j < rhs.size();)
    {
        if (lhs[i] <= rhs[j]) r[k++] = lhs[i++];
        else r[k++] = rhs[j++];
    }
    while (i == lhs.size() && j < rhs.size()) r[k++] = rhs[j++];
    while (j == rhs.size() && i < lhs.size()) r[k++] = lhs[i++];
    return r;
}

void testingMergeList()
{
    SeqList<int> lhs{0, 1, 3, 6, 7, 8}, rhs{2, 4, 5, 6, 7, 9, 10, 11};
    cout << mergeList(lhs, rhs) << endl;
}

/*
 * question 8. swap(a1,a2..., b1,b2...)
 */
template<typename T, unsigned M>
inline void reverse(T (&array)[M], int i, int j)
{
    for (; i < j; ++i, --j)
    {
        std::swap(array[i], array[j]);
    }
}

template<typename T, unsigned M>
void swapRange(T (&array)[M], int m, int n)
{
    reverse(array, 0, m + n - 1);
    reverse(array, 0, n - 1);
    reverse(array, n, m + n - 1);
}

void testingSwapRange()
{
    int a[] = {0, 1, 2, 3, 4, 6, 7, 8, 9};
    swapRange(a, 4, 5);
    printArray(cout, a) << endl;
}

/*
 * question 9. search or insert.
 */

template<typename T>
int binarySearch(SeqList<T> &qL, T val)
{
    int lo = 0, hi = qL.size();
    while (lo < hi)
    {
        int mid = (lo + hi) / 2;
        val < qL[mid] ? hi = mid : lo = mid + 1;
    }
    return lo - 1;
}

template<typename T>
void insert(SeqList<T> &qL, int pos, T val)
{
    if (qL.size() == qL.capacity())
    {
        auto pT = new T[qL.cap_ = qL.size() * 2];
        for (int i = 0; i < qL.size(); ++i)
        {
            if (i < pos)
            {
                pT[i] = qL[i];
            }
            else
            {
                pT[i + 1] = qL[i];
            }
        }
        pT[pos] = val;
        delete[] qL.pData_;
        qL.pData_ = pT;
        ++qL.size_;
    }
    else
    {
        for (int j = qL.size(); j > pos; --j)
        {
            qL[j] = qL[j - 1];
        }
        qL[pos] = val;
        ++qL.size_;
    }
}

template<typename T>
void searchOrInsert(SeqList<T> &qL, T val)
{
    int index = binarySearch(qL, val);
    if (qL[index] == val && index + 1 < qL.size())
    {
        std::swap(qL[index], qL[index + 1]);
    }
    else if (qL[index] != val)
    {
        insert(qL, index + 1, val);
    }
}

void testingSearchOrInsert()
{
    SeqList<int> qL{0, 1, 2, 3, 3, 5, 8, 9};
    searchOrInsert(qL, 4);
    cout << qL << endl;
    searchOrInsert(qL, 5);
    cout << qL << endl;
    searchOrInsert(qL, 9);
    cout << qL << endl;
    searchOrInsert(qL, 10);
    cout << qL << endl;
    searchOrInsert(qL, -1);
    cout << qL << endl;
}

/*
 * question 10. circle left move
 */
template<typename T, unsigned M>
void circulationLeftMove(T (&array)[M], int p)
{
    reverse(array, 0, M - 1);
    reverse(array, 0, M - p - 1);
    reverse(array, M - p, M - 1);
}

void testingCirculationLeftMove()
{
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    circulationLeftMove(a, 4);
    printArray(cout, a) << endl;
}

/*
 * question 11. find median number
 */
template<typename T>
T findMedian(const SeqList<T> &lhs, const SeqList<T> &rhs)
{
    SeqList<T> r = mergeList(lhs, rhs);
    if (r.size() & 1) return r[(r.size() - 1) / 2];
    else return r[r.size() / 2 - 1];
}

void testingFindMedian()
{
    SeqList<int> lhs = {11, 13, 15, 17, 19, 21}, rhs = {2, 4, 6, 8, 20};

    cout << findMedian(lhs, rhs) << endl;
}

/*
 * question 12. main element
 */

template<unsigned M>
bool checkMoreThanHalf(const int (&A)[M], int val)
{
    int times = 0;
    for (int i = 0; i < M; ++i)
    {
        if (val == A[i]) ++times;
    }
    if (times * 2 > M) return true;
    return false;
}

template<unsigned M>
int mainElement(const int (&A)[M])
{
    int times = 1, result = A[0];
    for (int i = 1; i < M; ++i)
    {
        if (times == 0)
        {
            times = 1;
            result = A[i];
        }
        else if (result == A[i])
        {
            ++times;
        }
        else
        {
            --times;
        }
    }
    if (checkMoreThanHalf(A, result)) return result;
    return -1;
}

void testingMainElement()
{
    int A[] = {0, 5, 5, 3, 5, 7, 5, 5};
    cout << mainElement(A) << endl;
    int a[] = {0, 5, 5, 3, 5, 1, 5, 7};
    cout << mainElement(a) << endl;
}

/*
 * question 13. The smallest positive integer that does not appear in the array.
 */
template<unsigned M>
inline int max(const int (&A)[M])
{
    int max = A[0];
    for (int i = 1; i < M; ++i)
    {
        if (max<A[i]) max = A[i];
    }
    return max;
}

template<typename T, unsigned M>
int binarySearch(const T (&A)[M], int lo, int hi, T val)
{
    while (lo < hi)
    {
        int mid = (lo + hi) / 2;
        val < A[mid] ? hi = mid : lo = mid + 1;
    }
    return lo - 1;
}

/*
 * partition of A[lo, hi]
 */

template<typename T, unsigned M>
int partition(T (&A)[M], int lo, int hi)
{
    T pivot = A[lo];
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

/*
 * sort of A[lo, hi)
 */
template<typename T, unsigned M>
void quickSort(T (&A)[M], int lo, int hi)
{
    if (hi - lo < 2) return;
    int mid = partition(A, lo, hi - 1);
    quickSort(A, lo, mid);
    quickSort(A, mid + 1, hi);

}

template<unsigned M>
int notAppearedInteger(int (&A)[M])
{
    quickSort(A, 0, M);
    int m = A[M - 1];
    int positiveMaxNum = 0 < m ? m + 1 : 1;
    for (int i = 1; i < positiveMaxNum; ++i)
    {
        int index = binarySearch(A, 0, M, i);
        if (A[index] != i) return i;
    }
    return positiveMaxNum;
}

void testingNotAppearedInteger()
{
    int A[] = {-5, 3, 2, 3}, a[] = {1, 2, 3, 4};
    cout << notAppearedInteger(A) << endl;
    cout << notAppearedInteger(a) << endl;
}

}

namespace linkedList {
template<typename T>
struct ForwardListNode
{
    template<typename... Args>
    explicit ForwardListNode(Args &&... args) : val_(std::forward<Args>(args)...), next_(nullptr)
    {
    }

    T val_;
    ForwardListNode *next_;
};

template<typename T> using ForwardNode = ForwardListNode<T>;

template<typename T>
struct LinkedListNode
{
    template<typename... Args>
    explicit LinkedListNode(Args &&... args) : val_(std::forward<Args>(args)...), prev_(nullptr), next_(nullptr)
    {
    }

    T val_;
    LinkedListNode *prev_;
    LinkedListNode *next_;
};

template<typename T> using LinkedNode = LinkedListNode<T>;

template<typename T>
struct ForwardList
{
    ForwardList() : head_(nullptr), first_(nullptr), size_(0)
    {
        init();
    }

    ForwardList(std::initializer_list<T> li);

    bool empty() const noexcept
    {
        return size_ == 0;
    }

    int size() const noexcept
    {
        return size_;
    }

    ForwardNode<T> *head_, *first_;
    int size_;

    ~ForwardList()
    {
        clear();
        delete head_;
    }

    void clear();

private:

    void init()
    {
        head_ = new ForwardNode<T>();
    }

};

template<typename T>
std::ostream &operator<<(std::ostream &os, const ForwardList<T> &rhs)
{
    os << '[';
    ForwardNode<T> *curr = rhs.first_;
    for (int i = 0; i < rhs.size_; ++i)
    {
        if (i != rhs.size_ - 1)
        {
            curr->val_ < 0 ? os << "(" << curr->val_ << ")-" : os << curr->val_ << "-";
        }
        else
        {
            curr->val_ < 0 ? os << "(" << curr->val_ << ")" : os << curr->val_;
        }
        curr = curr->next_;
    }
    os << ']';
    return os;
}

template<typename T>
void ForwardList<T>::clear()
{
    ForwardNode<T> *p = head_, *q;
    for (int i = 0; i < size_; ++i)
    {
        q = p->next_;
        p->next_ = q->next_;
        delete q;
    }
    size_ = 0;
    first_ = nullptr;
}

template<typename T>
ForwardList<T>::ForwardList(std::initializer_list<T> li) : ForwardList()
{
    ForwardNode<T> *curr = head_, *next;
    for (auto e : li)
    {
        next = new ForwardNode<T>(e);
        curr->next_ = next;
        curr = next;
        ++size_;
    }
    first_ = head_->next_;
}

void testingForwardList()
{
    ForwardList<int> li = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << li << endl;
    cout << li.size() << endl;
    cout << li.empty() << endl;
}

/*
 * Question 1: recursive delete x.
 */
template<typename T>
void recursiveDeleteOfValue(ForwardNode<T> *curr, T x, int &xTimes)
{
    if (curr == nullptr) return;
    if (curr->val_ != x) return recursiveDeleteOfValue(curr->next_, x, xTimes);
    else
    {
        if (auto p = curr->next_)
        {
            curr->next_ = p->next_;
            curr->val_ = p->val_;
            delete p;
            ++xTimes;
            return recursiveDeleteOfValue(curr, x, xTimes);
        }
        else
        {
            delete curr;
            ++xTimes;
        }
    }
}

template<typename T>
int recursiveDeleteX(ForwardList<T> &fL, T x)
{
    int xTimes = 0;
    recursiveDeleteOfValue(fL.first_, x, xTimes);
    fL.size_ -= xTimes;
    return xTimes;
}

void testingRecursiveDeleteX()
{
    ForwardList<int> fl{0, 1, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 2, 8, 2, 9, 2};
    cout << recursiveDeleteX(fl, 2) << endl;
    cout << fl << endl;
    ForwardList<int> fl1{2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 2, 8, 2, 9, 2};
    cout << recursiveDeleteX(fl1, 2) << endl;
    cout << fl1 << endl;
    ForwardList<int> fl2{2, 2, 2, 2};
    cout << recursiveDeleteX(fl2, 2) << endl;
    cout << fl2 << endl;
}

/*
 * Question 2: delete the value of x.
 */
template<typename T>
int deleteValueOfX(ForwardList<T> &fL, T x)
{
    if (!fL.first_) return 0;
    ForwardNode<T> *prev = fL.head_, *curr = prev->next_;
    int xTimes = 0;
    while (curr)
    {
        if (curr->val_ != x)
        {
            prev = curr;
            curr = curr->next_;
        }
        else
        {
            prev->next_ = curr->next_;
            delete curr;
            ++xTimes;
            curr = prev->next_;
        }
    }
    fL.size_ -= xTimes;
    fL.first_ = fL.head_->next_;
    return xTimes;
}

void testingDeleteValueOfX()
{
    ForwardList<int> fl{0, 1, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 2, 8, 2, 9, 2};
    cout << deleteValueOfX(fl, 2) << endl;
    cout << fl << endl;
    ForwardList<int> fl1{2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 2, 8, 2, 9, 2};
    cout << deleteValueOfX(fl1, 2) << endl;
    cout << fl1 << endl;
    ForwardList<int> fl2{2, 2, 2, 2};
    cout << deleteValueOfX(fl2, 2) << endl;
    cout << fl2 << endl;
}

/*
 * Question 3. reverse print.
 */

template<typename T>
void reversePrint(ForwardList<T> &fL)
{
    if (fL.empty()) return;
    ForwardNode<T> *p = fL.head_->next_, *q, *r;
    q = p->next_;
    while (q)
    {
        r = q->next_;
        q->next_ = p;
        p = q, q = r;
    }
    fL.head_->next_ = p;
    fL.first_ = p;
    cout << fL << endl;
}

void testingReversePrint()
{
    ForwardList<int> fL{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    reversePrint(fL);
}

/*
 * Question 3:delete the min of value.
 */

template<typename T>
void delMin(ForwardList<T> &fL)
{
    if (fL.empty()) return;
    ForwardNode<T> *p = fL.first_, *minP = p;
    while (p)
    {
        if (p->val_ < minP->val_)
        {
            minP = p;
        }
        p = p->next_;
    }

    if (auto q = minP->next_)
    {
        minP->next_ = q->next_;
        minP->val_ = q->val_;
        delete p;
    }
    else
    {
        delete minP;
    }

    --fL.size_;
    fL.first_ = fL.head_->next_;
}

void testingDelMin()
{
    ForwardList<int> fL{9, 3, 2, 3, 7, 9, 9, 10, 7, 0};
    delMin(fL);
    cout << fL << endl;
    ForwardList<int> fL2{9, 3, 2, 3, 0, 9, 9, 10, 7, 5};
    delMin(fL2);
    cout << fL2 << endl;
}

/*
 * Question 5. reverse
 */

template<typename T>
void reverse(ForwardList<T> &fL)
{
    if (fL.size() < 2) return;
    ForwardNode<T> *p = fL.head_, *q = p->next_, *r;
    while (q)
    {
        r = q->next_;
        q->next_ = p;
        p = q, q = r;
    }
    fL.head_->next_ = p;
    fL.first_ = p;
}

void testingReverse()
{
    ForwardList<int> fL{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    reverse(fL);
    cout << fL << endl;
    ForwardList<int> fL1{0};
    reverse(fL1);
    cout << fL1 << endl;

}

/*
 * Question 6: insert sort.
 */
template<typename T>
void insertSort(ForwardList<T> &fL)
{
    if (fL.size() < 2) return;
    auto p = fL.head_->next_;
    while (p)
    {
        auto q = p->next_;
        while (q && p->val_ <= q->val_)
        {
            p = q;
            q = q->next_;
        }
        if (q == nullptr) break;
        p->next_ = q->next_;
        auto t = fL.head_->next_;
        while (t && t->val_ <= q->val_) t = t->next_;
        q->next_ = t->next_;
        t->next_ = q;
        std::swap(t->val_, q->val_);
    }

    fL.first_ = fL.head_->next_;
}

void testingInsertSort()
{
    ForwardList<int> fL{9, 6, 2, 2, 5, 4, 0, 1, 8, 3, 7};
    insertSort(fL);
    cout << fL << endl;
    ForwardList<int> fL2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    insertSort(fL2);
    cout << fL2 << endl;
    ForwardList<int> fL3{1, 0};
    insertSort(fL3);
    cout << fL3 << endl;
}

/*
 * Question 7: delete elem that if the condition is true.
 */
template<typename T>
inline bool isValueOfRange(ForwardNode<T> *p, T b, T e)
{
    return p->val_ <= e && b <= p->val_;
}

template<typename T, typename F>
int deleteElemIf(ForwardList<T> &fL, F f)
{
    ForwardNode<T> *p = fL.head_;
    int cnt = 0;
    while (p)
    {
        auto q = p->next_;
        if (q && f(q))
        {
            p->next_ = q->next_;
            if (q == fL.first_)
            {
                fL.head_->next_ = q->next_;
                fL.first_ = fL.head_->next_;
            }
            delete q;
            ++cnt;
            --fL.size_;
        }
        p = p->next_;
    }
    return cnt;
}

void testingDeleteElemIf()
{
    ForwardList<int> fL{9, 6, 2, 2, 5, 4, 0, 1, 8, 3, 7};
    using namespace std::placeholders;
    deleteElemIf(fL, std::bind(isValueOfRange<int>, _1, 5, 8));
    cout << fL << endl;
}

/*
 * Question 8: find the common node.
 */

template<typename T>
ForwardNode<T> *findCommonNode(ForwardNode<T> &lL, ForwardNode<T> &rL)
{
    int m = 0, n = 0;
    ForwardNode<T> *p = lL.next_, *q = rL.next_;
    while (p)
    {
        p = p->next_;
        ++m;
    }
    while (q)
    {
        q = q->next_;
        ++n;
    }
    p = lL.next_, q = rL.next_;
    int mn = m - n;
    if (mn < 0)
    {
        mn = -mn;
        while (mn--) q = q->next_;
    }
    else if (mn > 0)
    {
        while (mn--) p = p->next_;
    }

    while (p)
    {
        if (p == q) return p;
        p = p->next_;
        q = q->next_;
    }

    return nullptr;
}

void testingFindCommonNode()
{
    ForwardNode<int> head, n1(2), n2(5), n3(7), n4(6), n5(8);
    ForwardNode<int> headr, m1(12), m2(13), m3(14);
    head.next_ = &n1;
    n1.next_ = &n2;
    n2.next_ = &n3;
    n3.next_ = &n4;
    n4.next_ = &n5;
    headr.next_ = &m1;
    m1.next_ = &m2;
    m2.next_ = &m3;
    m3.next_ = &n2;
    auto p = findCommonNode(head, headr);
    if (p)
        cout << p->val_ << endl;
}

/*
 * Question 9. sort the list and print and free the sapce.
 */
void printElemAndFree(ForwardList<int> &fL)
{
    insertSort(fL);
    cout << fL << endl;
    fL.clear();
}

void testingPrintElemAndFree()
{
    ForwardList<int> fL{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    printElemAndFree(fL);
}

/*
 * Question 10: separate into list whitch only contains even and odd nums.
 */
template<typename T>
void separateIntoOddAndEven(ForwardList<T> &fL, ForwardList<T> &oddL, ForwardList<T> &evenL)
{
    auto p = fL.head_->next_;
    auto s = oddL.head_;
    auto t = evenL.head_;
    while (p)
    {
        if (p->val_ & 1)
        {
            s->next_ = new ForwardNode<T>(p->val_);
            s = s->next_;
            ++oddL.size_;
        }
        else
        {
            t->next_ = new ForwardNode<T>(p->val_);
            t = t->next_;
            ++evenL.size_;
        }
        p = p->next_;
    }
    oddL.first_ = oddL.head_->next_;
    evenL.first_ = evenL.head_->next_;
}

void testingSeparateIntoOddAndEven()
{
    ForwardList<int> fL{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ForwardList<int> oddL, evenL;
    separateIntoOddAndEven(fL, oddL, evenL);
    cout << fL << endl;
    cout << oddL << endl;
    cout << evenL << endl;
}

/*
 * Question 11: C{a1, b1, a2, b2,...} separate into A{a1, a2...} and B{bn, bn-1,...}
 */

template<typename T>
void separateIntoAboveTraits(ForwardList<T> &fL, ForwardList<T> &aL, ForwardList<T> &bL)
{
    auto p = fL.head_->next_;
    auto s = aL.head_;
    auto t = bL.head_;
    bool flag = true;
    while (p)
    {
        if (flag)
        {
            s->next_ = new ForwardNode<T>(p->val_);
            s = s->next_;
            ++aL.size_;
            flag = false;
        }
        else
        {
            if (bL.size_ == 0)
            {
                t->next_ = new ForwardNode<T>(p->val_);
                ++bL.size_;
                flag = true;
            }
            else
            {
                auto r = new ForwardNode<T>(p->val_);
                r->next_ = t->next_;
                t->next_ = r;
                ++bL.size_;
                flag = true;
            }
        }
        p = p->next_;
    }
    aL.first_ = aL.head_->next_;
    bL.first_ = bL.head_->next_;
}

void testingSeparateIntoAboveTraits()
{
    ForwardList<int> fL{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ForwardList<int> aL, bL;
    separateIntoAboveTraits(fL, aL, bL);
    cout << fL << endl;
    cout << aL << endl;
    cout << bL << endl;
}

/*
 * Question 12: unique
 */

template<typename T>
int unique(ForwardList<T> &fL)
{
    int cnt = 0;
    ForwardNode<T> *p = fL.first_, *q;
    while (p->next_)
    {
        q = p->next_;
        if (p->val_ != q->val_)
        { p = q; }
        else
        {
            p->next_ = q->next_;
            delete q;
            ++cnt;
        }
    }
    fL.size_ -= cnt;
    fL.first_ = fL.head_->next_;
    return cnt;
}

void testingUnique()
{
    ForwardList<int> fL{7, 10, 10, 21, 30, 42, 42, 42, 51, 70};
    auto cnt = unique(fL);
    cout << fL << endl;
    cout << "cnt = " << cnt << endl;
}

/*
 * Question 13: merge
 */
template<typename T>
void mergeDecrease(ForwardList<T> &aL, ForwardList<T> &bL, ForwardList<T> &fL)
{
    ForwardNode<T> *p = aL.first_, *q = bL.first_, *h = fL.head_, *r;
    while (p && q)
    {
        if (p->val_ <= q->val_)
        {
            r = p->next_;
            if (h->next_)
            {
                p->next_ = h->next_;
                h->next_ = p;
            }
            else
            {
                h->next_ = p;
            }
            p = r;
        }
        else
        {
            r = q->next_;
            if (h->next_)
            {
                q->next_ = h->next_;
                h->next_ = q;
            }
            else
            {
                h->next_ = q;
            }
            q = r;
        }
    }
    while (p && q == nullptr)
    {
        r = p->next_;
        p->next_ = h->next_;
        h->next_ = p;
        p = r;
    }
    while (q && p == nullptr)
    {
        r = q->next_;
        q->next_ = h->next_;
        h->next_ = q;
        q = r;
    }
    fL.size_ = aL.size_ + bL.size_;
    fL.first_ = fL.head_->next_;
}

void testingMergeDecrease()
{
    ForwardList<int> aL{0, 2, 4, 6, 8}, bL{1, 3, 5, 7, 9}, fL;
    mergeDecrease(aL, bL, fL);
    cout << fL << endl;
}

/*
 * Question 14: Intersection
 */
template<typename T>
void orderedIntersection(ForwardList<T> &aL, ForwardList<T> &bL, ForwardList<T> &fL)
{
    ForwardNode<T> *p = aL.first_, *q = bL.first_, *h = fL.head_;
    while (p && q)
    {
        if (p->val_ < q->val_) p = p->next_;
        else if (q->val_ < p->val_) q = q->next_;
        else
        {
            h->next_ = new ForwardNode<T>(p->val_);
            ++fL.size_;
            h = h->next_;
            p = p->next_;
            q = q->next_;
        }
    }
    fL.first_ = fL.head_->next_;
}

void testingOrderedIntersection()
{
    ForwardList<int> aL{0, 2, 3, 4, 6, 8}, bL{1, 3, 5, 6, 7, 8, 9}, fL;
    orderedIntersection(aL, bL, fL);
    cout << fL << endl;
    ForwardList<int> aL1{0, 2, 4, 6, 8}, bL1{1, 3, 5, 7, 9}, fL1;
    orderedIntersection(aL1, bL1, fL1);
    cout << fL1 << endl;
    ForwardList<int> aL2{0, 1, 1, 2, 3, 3, 5}, bL2{1, 2, 2, 3, 3, 4, 5, 5, 7, 9}, fL2;
    orderedIntersection(aL2, bL2, fL2);
    cout << fL2 << endl;
}

/*
 * Question 15: order intersection.
 */
template<typename T>
void b2AIntersection(ForwardList<T> &aL, ForwardList<T> &bL)
{
    ForwardNode<T> *lp = aL.head_, *p = lp->next_, *q = bL.head_->next_, *rp;
    while (p && q)
    {
        if (q->val_ < p->val_) q = q->next_;
        else if (p->val_ < q->val_)
        {
            rp = p->next_;
            lp->next_ = p->next_;
            p = rp;
            --aL.size_;
        }
        else
        {
            lp = p;
            p = p->next_;
            q = q->next_;
        }
    }

    while (p && q == nullptr)
    {
        lp->next_ = p->next_;
        delete p;
        p = lp->next_;
        --aL.size_;
    }

    aL.first_ = aL.head_->next_;
}

void testingB2AIntersection()
{
    ForwardList<int> aL{2, 3, 6, 7, 9, 10}, bL{1, 3, 5, 7};
    b2AIntersection(aL, bL);
    cout << aL << endl;
    cout << bL << endl;
    ForwardList<int> aL2{2, 4, 6, 8, 9, 10}, bL2{1, 3, 5, 7};
    b2AIntersection(aL2, bL2);
    cout << aL2 << endl;
    cout << bL2 << endl;
}

/*
 * Question 16: sub sequence
 */
template<typename T>
bool bIsASubSequence(ForwardList<T> &aL, ForwardList<T> &bL)
{
    int n = aL.size(), m = bL.size();
    if (n < m) return false;
    int t = n - m + 1;
    ForwardNode<T> *p = aL.head_->next_, *q, *rp;
    while (t--)
    {
        q = bL.head_->next_, rp = p;
        while (q)
        {
            if (q->val_ == rp->val_)
            {
                q = q->next_;
                rp = rp->next_;
            }
            else
            {
                break;
            }
        }
        if (q == nullptr) return true;
        p = p->next_;
    }
    return false;
}

void testingBIsASubSequence()
{
    ForwardList<int> aL{5, 7, 5, 7, 8}, bL{5, 7, 8};
    cout << bIsASubSequence(aL, bL) << endl;
}

/*
 * Question 17: the is circle list is symmetrical.
 */
template<typename T>
bool isSymmetrical(LinkedNode<T> *h)
{
    LinkedNode<T> *p = h->next_, *q = h->prev_;
    while (p != q)
    {
        if (p->val_ == q->val_)
        {
            p = p->next_;
            q = q->prev_;
        }
        else
        {
            break;
        }
    }
    if (p == q) return true;
    return false;
}

void testingIsSymmetrical()
{
    LinkedNode<int> h, n1(2), n2(3), n3(5), n4(3), n5(2);
    h.next_ = &n1, n1.next_ = &n2, n2.next_ = &n3;
    n3.next_ = &n4, n4.next_ = &n5, n5.next_ = &h;

    h.prev_ = &n5, n5.prev_ = &n4, n4.prev_ = &n3;
    n3.prev_ = &n2, n2.prev_ = &n1, n1.prev_ = &h;
    cout << isSymmetrical(&h) << endl;
}

/*
 * Question 18. form the large circle.
 */
template<typename T>
void bLAttachAL(ForwardList<T> &aL, ForwardList<T> &bL)
{
    ForwardNode<T> *p = aL.head_, *ah = p, *q = bL.head_, *bh = q;
    while (ah != p->next_)
    { p = p->next_; }
    while (bh != q->next_)
    { q = q->next_; }
    p->next_ = bh;
    q->next_ = ah;
}

/*
 * Question 19: find the min value and deleted in circle list.
 */
template<typename T>
void deleteMinInCircle(ForwardList<T> &cL)
{
    ForwardNode<T> *h = cL.head_, *p, *preMinP;
    int n = cL.size();
    while (n--)
    {
        p = preMinP = h;
        while (h != p->next_)
        {
            if (p->next_->val_ < preMinP->next_->val_)
            {
                preMinP = p;
            }
            p = p->next_;
        }
        cout << preMinP->next_->val_ << " ";
        auto r = preMinP->next_;
        preMinP->next_ = r->next_;
        delete r;
    }
    cL.size_ = 0;
}

void testingDeleteMinInCircle()
{
    ForwardList<int> cL{8, 3, 2, 4, 3, 1, 7};
    int n = cL.size();
    auto p = cL.head_->next_;
    while (--n)
    { p = p->next_; }
    p->next_ = cL.head_;

    deleteMinInCircle(cL);

}

/*
 * Question 20: LFU algorithm
 */

template<typename T>
struct FrequencyLinkedList
{
    FrequencyLinkedList() : head_(new Node), size_(0)
    {
    }

    FrequencyLinkedList(std::initializer_list<T> li);

    ~FrequencyLinkedList()
    {
        clear();
        delete head_;
    }

private:
    void clear()
    {
        Node *h = head_, *p;
        for (int i = 0; i < size_; ++i)
        {
            p = h->next_;
            h->next_ = p->next_;
            delete p;
        }
        size_ = 0;
    }

public:
    struct Node
    {
        template<typename... Args>
        explicit Node(Args &&... args)
                : data_(std::forward<Args>(args)...), freq_(0), prev_(nullptr), next_(nullptr)
        {
        }

        T data_;
        int freq_;
        Node *prev_;
        Node *next_;
    };

    Node *head_;
    int size_;

};

template<typename T> using LFUNode = typename FrequencyLinkedList<T>::Node;

template<typename T>
std::ostream &operator<<(std::ostream &os, const FrequencyLinkedList<T> &rhs)
{
    LFUNode<T> *p = rhs.head_;
    os << '{';
    for (int i = 0; i < rhs.size_; ++i)
    {
        p = p->next_;
        if (i != rhs.size_ - 1)
        {
            os << "(" << p->data_ << ":" << p->freq_ << ")" << "-";
        }
        else
        {
            os << "(" << p->data_ << ":" << p->freq_ << ")";
        }
    }
    os << '}';
    return os;
}

template<typename T>
FrequencyLinkedList<T>::FrequencyLinkedList(std::initializer_list<T> li) : FrequencyLinkedList()
{
    Node *p, *h = head_;
    for (auto e : li)
    {
        p = new Node(e);
        h->next_ = p;
        p->prev_ = h;
        h = h->next_;
        ++size_;
    }
}

template<typename T>
LFUNode<T> *Locate(FrequencyLinkedList<T> &fL, T x)
{
//        1. find the value of x.
    LFUNode<T> *p = fL.head_->next_, *xp = nullptr;
    while (p)
    {
        if (p->data_ == x)
        {
            xp = p;
            ++xp->freq_;
            break;
        }
        p = p->next_;
    }
    if (p == nullptr) return xp;

//        2.sort by frequency.
    p = fL.head_->next_;
    if (p == nullptr || p->next_ == nullptr) return xp;
    LFUNode<T> *lp, *rp;
    while (p->next_)
    {
        rp = p->next_;
        while (rp && rp->freq_ <= p->freq_)
        {
            p = rp;
            rp = rp->next_;
        }
        if (rp == nullptr) break;

        lp = p;
        while (lp != fL.head_ && lp->freq_ <= rp->freq_)
        {
            lp = lp->prev_;
        }

        if (rp->next_)
        {
            p->next_ = rp->next_;
            rp->next_->prev_ = p;

            rp->next_ = lp->next_;
            lp->next_->prev_ = rp;
            lp->next_ = rp;
            rp->prev_ = lp;
        }
        else
        {
            p->next_ = rp->next_;

            rp->next_ = lp->next_;
            lp->next_->prev_ = rp;
            lp->next_ = rp;
            rp->prev_ = lp;
        }
    }


//        3.move the pointer of xp, that makes it near the header.


    lp = xp->prev_;
    bool notMoved = true;
    while (lp != fL.head_ && lp->freq_ == xp->freq_)
    {
        lp = lp->prev_;
        notMoved = false;
    }

    if (notMoved) return xp;

    if (xp->next_)
    {
        xp->prev_->next_ = xp->next_;
        xp->next_->prev_ = xp->prev_;

        xp->next_ = lp->next_;
        lp->next_->prev_ = xp;
        lp->next_ = xp;
        xp->prev_ = lp;
    }
    else
    {
        xp->prev_->next_ = xp->next_;

        xp->next_ = lp->next_;
        lp->next_->prev_ = xp;
        lp->next_ = xp;
        xp->prev_ = lp;
    }
    return xp;
}

void testingLocate()
{
    static std::default_random_engine e;
    static std::uniform_int_distribution<unsigned> u(0, 15);
    FrequencyLinkedList<unsigned> fL{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    for (int i = 0; i < 9172; ++i)
    {
        Locate(fL, u(e));
    }
    cout << fL << endl;
}

/*
 * Question 21: find the k-th last in given of the list.
 */
template<typename T>
int findKthLastOf(ForwardList<T> &fL, int k)
{
    int n = fL.size(), m = n - k + 1;
    if (m < 1) return 0;
    auto p = fL.head_;
    while (m--)
    {
        p = p->next_;
    }

    cout << p->val_ << endl;
    return 1;
}

/*
 * Question 22: find the common Node. equals to Question 8.
 */
template<typename T>
ForwardNode<T> *findCommonNode(ForwardList<T> &aL, ForwardList<T> &bL)
{
    ForwardNode<T> *p = aL.head_->next_, *q = bL.head_->next_;
    int n = aL.size(), m = bL.size();
    int nm = n - m;
    if (nm < 0)
    {
        nm = -nm;
        while (nm--) q = q->next_;
    }
    else if (0 < nm)
    {
        while (nm--) p = p->next_;
    }

    while (p && q)
    {
        if (p == q) return p;
        else
        {
            p = p->next_;
            q = q->next_;
        }
    }
    return nullptr;
}

/*
 * Question 23: absolute the value and duplicate
 */


template<typename T>
void absDuplication(ForwardList<T> &fL, int n)
{
    T *aux = new T[n + 1];
    for (int i = 0; i < n + 1; ++i)
    {
        aux[i] = T();
    }
    ForwardNode<T> *lp = fL.head_, *p = lp->next_;
    while (p)
    {
        if (aux[std::abs(p->val_)])
        {
            lp->next_ = p->next_;
            delete p;
            --fL.size_;
            p = lp->next_;
        }
        else
        {
            ++aux[std::abs(p->val_)];
            lp = p;
            p = p->next_;
        }
    }
}

void testingAbsDuplication()
{
    ForwardList<int> fL{21, -15, -15, -7, 15};
    absDuplication(fL, 21);
    cout << fL << endl;
}
}

namespace stackAndQueue {

/*
 * Page 66. Question 3(2) is the sequence legal?
 */

bool isLegalOfOperatingStack(linear::Stack<int> &s, const char *p)
{
    while (p && *p)
    {
        if (*p == 'I')
        {
            s.push(42);
        }
        else
        {
            if (s.empty()) return false;
            s.pop();
        }
        ++p;
    }
    if (!s.empty()) return false;
    return true;
}

void testingIsLegalOfOperatingStack()
{
    linear::Stack<int> s;
    const char *arr[4] = {"IOIIOIOO", "IOOIOIIO", "IIIOIOIO", "IIIOOIOO"};
    for (int i = 0; i < 4; ++i)
    {
        cout << isLegalOfOperatingStack(s, arr[i]) << " ";
        s.clear();
    }
}

/*
 * Page 66. Question 4. is the list, stores character, is symmetrical ?
 */
bool isStoreCharSymmetrical(linkedList::ForwardList<char> &fL)
{
    int n = fL.size();
    char *inputs = new char[n + 1], *outs = new char[n + 1];
    linear::Stack<char> s;
    auto p = fL.head_;
    for (int i = 0; i < n; ++i)
    {
        p = p->next_;
        s.push(p->val_);
        inputs[i] = p->val_;
    }

    int j = 0;
    while (!s.empty())
    {
        outs[j++] = s.pop();
    }

    for (int k = 0; k < n; ++k)
    {
        if (inputs[k] != outs[k]) return false;
    }
    return true;
}

void testingIsStoreCharSymmetrical()
{
    linkedList::ForwardList<char> fL{'x', 'y', 'x'}, fL1{'x', 'y', 'y', 'x'};
    cout << isStoreCharSymmetrical(fL) << " ";
    cout << isStoreCharSymmetrical(fL1) << endl;
}

/*
 * Question 5. shared stack
 */

constexpr int MaxSize = 65535;

template<typename T>
struct SharedStack
{
    T S[MaxSize];
    int top1 = -1, top2 = MaxSize;
};

template<typename T>
bool lPush(SharedStack<T> &s1, T val)
{
    if (s1.top2 - s1.top1 == 1) return false;
    s1.S[++s1.top1] = val;
    return true;
}

template<typename T>
bool rPush(SharedStack<T> &s2, T val)
{
    if (s2.top2 - s2.top1 == 1) return false;
    s2.S[--s2.top2] = val;
    return true;
}

template<typename T>
bool lPop(SharedStack<T> &s1, T &val)
{
    if (s1.top1 == -1) return false;
    val = s1.S[s1.top1--];
    return true;
}

template<typename T>
bool rPop(SharedStack<T> &s2, T &val)
{
    if (s2.top2 == MaxSize) return false;
    val = s2.S[s2.top2++];
    return true;
}

void testingPushAndPop()
{
    SharedStack<int> s1, s2;
    int x1 = 0, x2 = 0;
    for (int i = 0; i < 6553; ++i)
    {
        cout << lPush(s1, x1) << rPush(s2, x2);
        if (i % 256 == 0) cout << endl;
    }
    for (int i = 0; i < 6353; ++i)
    {
        cout << lPop(s1, x1) << rPop(s2, x2);
        if (i % 256 == 0) cout << endl;
    }
}

/*
 * Page 81. Question 1: circle queue.
 */

template<typename T>
struct CircleQueue
{
    T S[MaxSize];
    int front_ = 0, rear_ = 0;
    int tag = 0;
};

template<typename T>
bool push(CircleQueue<T> &cQ, T x)
{
    if (cQ.tag == 1 && cQ.front_ == cQ.rear_) return false;
    cQ.S[cQ.rear_] = x;
    cQ.rear_ = (cQ.rear_ + 1) % MaxSize;
    cQ.tag = 1;
    return true;
}

template<typename T>
bool pop(CircleQueue<T> &cQ, T &x)
{
    if (cQ.tag == 0 && cQ.front_ == cQ.rear_) return false;
    x = cQ.S[cQ.front_];
    cQ.front_ = (cQ.front_ + 1) % MaxSize;
    cQ.tag = 0;
    return true;
}

void testingCircleStack()
{
    CircleQueue<int> cQ;
    int x = 0;
    for (int i = 0; i < 65535; ++i)
    {
        cout << push(cQ, i) << push(cQ, i) << pop(cQ, x);
        if (i % 40 == 0) cout << endl;
    }
}

/*
 * Question 2: use the stack for reversing the queue.
 */
template<typename T>
void reverseQueue(linear::Queue<T> &q)
{
    linear::Stack<T> s;
    while (!q.empty())
    {
        s.push(q.dequeue());
    }

    while (!s.empty())
    {
        q.enqueue(s.pop());
    }
}

void testingReverseQueue()
{
    linear::Queue<int> q;
    for (int i = 0; i < 10; ++i)
    {
        q.enqueue(i);
    }
    cout << q << endl;
    reverseQueue(q);
    cout << q << endl;
}

/*
 * Question 3: use two Stacks for simulating queue.
 */
template<typename T>
struct SimulateQueue
{
    bool empty() const noexcept
    {
        return s1.empty() && s2.empty();
    }

    void enqueue(T val)
    {
        s1.push(val);
    }

    bool dequeue(T &val)
    {
        if (empty()) return false;
        if (s2.empty())
        {
            while (!s1.empty())
            {
                s2.push(s1.pop());
            }
        }
        val = s2.pop();
        return true;
    }

private:
    linear::Stack<T> s1, s2;
};

void testingSimulateQueue()
{
    SimulateQueue<int> sq;
    int x;
    for (int i = 0; i < 100; ++i)
    {
        if (i < 50) sq.enqueue(i);
        else cout << (sq.dequeue(x) ? x : 0) << " ";
    }
}

/*
 * Page 90. Question 1: bracket matching
 * @param p ends of '\0'
 */
bool isBracketMatch(const char *p)
{
    linear::Stack<char> s;
    s.push('\0');
    while (!s.empty())
    {
        switch (*p++)
        {
            case '(':
                s.push('(');
                break;
            case '[':
                s.push('[');
                break;
            case '{':
                s.push('{');
                break;
            case ')':
            {
                if (s.top() != '(') return false;
                s.pop();
                break;
            }
            case '}':
            {
                if (s.top() != '{') return false;
                s.pop();
                break;
            }
            case ']':
            {
                if (s.top() != '[') return false;
                s.pop();
                break;
            }
            case '\0':
                if (s.top() != '\0') return false;
                s.pop();
                break;
            default:
                break;
        }

    }
    return true;
}

//
void testingIsBracketMatch()
{
    const char *p = "{3+({4 + 10} / 2 * [5 + 9]) / (4 + 3) *[(4+7)/(2+1)]}";
    cout << isBracketMatch(p) << endl;
}

/*
 * Question 2: train arrange.
 */
void trainArrange(char *train)
{
    char *p = train, *q = train;
    linear::Stack<char> s;
    while (*p)
    {
        if (*p == 'H')
        {
            s.push(*p);
        }
        else
        {
            *q++ = *p;
        }
        ++p;
    }
    while (!s.empty())
    {
        *q++ = s.pop();
    }
}

void testingTrainArrange()
{
    char train[] = {'S', 'H', 'S', 'H', 'S', 'S', 'H', 'H', 'H', 'S', 'H', '\0'};
    trainArrange(train);
    cout << train << endl;
}

/*
 * Question 3:
 * implements the function of Pn(x) = 1, n= 0;
 *                                  = 2x, n = 1;
 *                                  = 2xPn-1(x) - 2(n-1)Pn-2(x); n > 1;
 */

struct PnXStack
{
    struct Pnx;

    int top;
    Pnx *S;

    struct Pnx
    {
        int no_;
        double val_; // val_ = Px
    };
};

void initPnxStack(PnXStack &pnS, int n)
{
    pnS.top = -1;
    pnS.S = new PnXStack::Pnx[n + 1];
}

/*
 * version 1.0;
 */
double pNFunction(int n, double x)
{
    PnXStack pnS;
    initPnxStack(pnS, n);
    double fv1 = 1, fv2 = 2 * x;
    for (int i = n; i >= 2; --i)
    {
        ++pnS.top;
        pnS.S[pnS.top].no_ = i;
    }

    while (pnS.top >= 0)
    {
        pnS.S[pnS.top].val_ = 2 * x * fv2 - 2 * (pnS.S[pnS.top].no_ - 1) * fv1;
        fv1 = fv2;
        fv2 = pnS.S[pnS.top].val_;
        --pnS.top;
    }
    delete[] pnS.S;
    if (n == 0) return fv1;
    return fv2;
}

/*
 * version 2.0;
 */
double PFunction(int n, double x)
{
//        construct the function's item
    struct Item
    {
        int no_;
        double val_;
    };
    Item *S = new Item[n + 1];
//        simulate a stack
    int top = -1;
    for (int i = n; i > 1; --i)
    {
        S[++top].no_ = i;
    }

//        calculate the function's value
    double fv1 = 1, fv2 = 2 * x;
    while (top > -1)
    {
        S[top].val_ = 2 * x * fv2 - 2 * (S[top].no_ - 1) * fv1;
        fv1 = fv2;
        fv2 = S[top].val_;
        --top;
    }
    delete[] S;
    return fv2;
}

void testingPNFunction()
{
    cout << pNFunction(10, 2) << endl;
    cout << PFunction(10, 2) << endl;
}


/*
 * Question 4: simulate the ferry manger.
 */
/*
 * 1.create the type of passenger's car and lorry
 */
struct Vehicle
{
    virtual ~Vehicle() = default;
};

struct PassengerCar : Vehicle
{
};
struct Lorry : Vehicle
{
};

/*
 * 2.generate the vehicles.
 */

Vehicle **generateVehicles(int n)
{
    static std::default_random_engine e;
    Vehicle **v = new Vehicle *[n + 1];
    for (int i = 0; i < n; ++i)
    {
        if (e() & 1U)
        {
            v[i] = new PassengerCar;
        }
        else
        {
            v[i] = new Lorry;
        }
    }
    return v;
}

void ferryManager(linear::Queue<Vehicle *> &ferry, int n)
{
    Vehicle **S = generateVehicles(n);

    linear::Queue<Vehicle *> passengers;
    linear::Queue<Vehicle *> lorries;

    for (int i = 0; i < n; ++i)
    {
        if (typeid(*S[i]) == typeid(PassengerCar))
        {
            passengers.enqueue(S[i]);
        }
        else if (typeid(*S[i]) == typeid(Lorry))
        {
            lorries.enqueue(S[i]);
        }
    }

    int k = 0, pCnt = 0;
    while (k < 10)
    {
        if (!passengers.empty() && pCnt < 4)
        {
            ferry.enqueue(passengers.dequeue());
            ++pCnt;
            ++k;
        }
        else if (pCnt == 4 && !lorries.empty())
        {
            ferry.enqueue(lorries.dequeue());
            ++k;
            pCnt = 0;
        }
        else
        {
            while (k < 10 && pCnt < 4 && !lorries.empty())
            {
                ferry.enqueue(lorries.dequeue());
                ++pCnt;
                ++k;
            }
            pCnt = 0;

            if (passengers.empty() && lorries.empty())
            {
                k = 11;
            }

        }
    }

    for (int j = 0; j < n; ++j)
    {
        delete S[j];
    }
    delete[] S;
}

void testingFerryManger()
{
    linear::Queue<Vehicle *> ferry;
    ferryManager(ferry, 100);
}

}

}

void TestingStackAndQueue()
{
    using namespace linearList;
//    stackAndQueue::testingIsLegalOfOperatingStack();
//    stackAndQueue::testingIsStoreCharSymmetrical();
//    stackAndQueue::testingPushAndPop();
//    stackAndQueue::testingCircleStack();
//    stackAndQueue::testingReverseQueue();
//    stackAndQueue::testingSimulateQueue();
    stackAndQueue::testingIsBracketMatch();
    stackAndQueue::testingTrainArrange();
    stackAndQueue::testingPNFunction();
    stackAndQueue::testingFerryManger();
}

void TestingLinkedList()
{
    using namespace linearList;
    linkedList::testingForwardList();
    linkedList::testingRecursiveDeleteX();
    linkedList::testingDeleteValueOfX();
    linkedList::testingReversePrint();
    linkedList::testingDelMin();
    linkedList::testingReverse();
    linkedList::testingInsertSort();
    linkedList::testingDeleteElemIf();
    linkedList::testingFindCommonNode();
    linkedList::testingPrintElemAndFree();
    linkedList::testingSeparateIntoOddAndEven();
    linkedList::testingSeparateIntoAboveTraits();
    linkedList::testingUnique();
    linkedList::testingMergeDecrease();
    linkedList::testingOrderedIntersection();
    linkedList::testingB2AIntersection();
    linkedList::testingBIsASubSequence();
    linkedList::testingIsSymmetrical();
    linkedList::testingDeleteMinInCircle();
    linkedList::testingLocate();
    linkedList::testingAbsDuplication();
}

void TestingJosephus()
{
    josephus::Solve();
}

void TestingSequentialList()
{
    using namespace linearList;
    sequentialList::testingExerciseDelMin();
    sequentialList::testingReverse();
    sequentialList::testingDelX();
    sequentialList::testingDeleteRange();
    sequentialList::testingDeleteRepeats();
    sequentialList::testingMergeList();
    sequentialList::testingSwapRange();
    sequentialList::testingSearchOrInsert();
    sequentialList::testingCirculationLeftMove();
    sequentialList::testingFindMedian();
    sequentialList::testingMainElement();
    sequentialList::testingNotAppearedInteger();
}

int main(int argc, char *argv[])
{
    TestingStackAndQueue();
    return 0;
}







