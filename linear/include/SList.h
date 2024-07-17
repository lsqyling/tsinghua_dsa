//
// Created by shiqing on 2020/5/13.
//

#ifndef TSINGHUA_DATASTRUCTURE_SLIST_H
#define TSINGHUA_DATASTRUCTURE_SLIST_H

#include <memory>
#include <iostream>
#include <cassert>
#include <random>

namespace linear {
template<typename T>
struct ListNode
{
    T data_;
    ListNode *prev_, *next_;

    template<typename ...Args>
    explicit ListNode(Args &&...params)
            : data_(std::forward<Args>(params)...), prev_(nullptr), next_(nullptr)
    {
    }
};

template<typename>
class SList;

template<typename T>
std::ostream &operator<<(std::ostream &os, const SList<T> &rhs);

template<typename T>
class SList
{
    friend std::ostream &operator
    <<<T>(
    std::ostream &os,
    const SList &rhs
    );
public:
    using Node = ListNode<T>;

    SList();

    SList(const SList &rhs);

    SList &operator=(const SList &rhs);

    SList(const SList &rhs, int s, int n);

    SList(Node *pos, int n);

    ~SList();

    /*
     * readable interface
     */
    int size() const;

    bool empty() const;

    T &operator[](int r);

    const T &operator[](int r) const;

    Node *first() const;

    Node *last() const;

    bool vaild(Node *p) const;

    int disordered() const;

    Node *find(const T &e) const;

    Node *find(const T &e, int n, Node *p) const;

    Node *search(const T &e) const;

    Node *search(const T &e, int n, Node *p) const;

    Node *selectMax(Node *p, int n) const;

    Node *selectMax() const;

    /*
     * writeable interface
     */
    Node *insertAsFirst(const T &e);

    Node *insertAsLast(const T &e);

    Node *insertPrev(Node *p, const T &e);

    Node *insertSucc(Node *p, const T &e);

    T remove(Node *p);

    void clear();

    void merge(SList &L);

    void sort(Node *p, int n);

    void sort();

    int deduplicate();

    int uniquify();

    void reverse();

    /*
     * traversal
     */
    void traverse(void (*pf)(T &e));

    template<typename F>
    void traverse(F f);

private:
    void selectSort(Node *p, int n);

    void insertSort(Node *p, int n);

    Node *head_, *tail_;
    int size_;
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const SList<T> &rhs)
{
    os << '[';
    auto p = rhs.first();
    while (p != rhs.tail_)
    {
        os << p->data_;
        if (p != rhs.last()) os << " ";
        p = p->next_;
    }
    os << ']';
    return os;
}

template<typename T>
SList<T>::SList() : head_(new Node), tail_(new Node), size_(0)
{
    head_->next_ = tail_;
    tail_->prev_ = head_;
}

template<typename T>
SList<T>::SList(const SList &rhs) : SList()
{
    Node *p = rhs.first(), *pos = head_;
    while (p != rhs.tail_)
    {
        Node *node = new Node(p->data_);
        pos->next_ = node;
        node->prev_ = pos;
        p = p->next_;
        pos = pos->next_;
        ++size_;
    }
    pos->next_ = tail_;
    tail_->prev_ = pos;
}

template<typename T>
SList<T> &SList<T>::operator=(const SList &rhs)
{
    if (this != &rhs)
    {
        clear();
        Node *p = rhs.first();
        while (p != rhs.tail_)
        {
            insertAsLast(p->data_);
            p = p->next_;
        }
    }
    return *this;
}

template<typename T>
SList<T>::SList(const SList &rhs, int s, int n) : SList()
{
    Node *ps = rhs.first(), *p = head_;
    while (s--) ps = ps->next_;
    while (n-- && ps != rhs.tail_)
    {
        Node *node = new Node(ps->data_);
        p->next_ = node;
        node->prev_ = p;
        ps = ps->next_;
        p = p->next_;
        ++size_;
    }
    p->next_ = tail_;
    tail_->prev_ = p;
}

template<typename T>
SList<T>::SList(SList::Node *pos, int n) : SList()
{
    Node *h = head_;
    while (n--)
    {
        Node *node = new Node(pos->data_);
        h->next_ = node;
        node->prev_ = h;
        h = h->next_;
        pos = pos->next_;
        ++size_;
    }
    h->next_ = tail_;
    tail_->prev_ = h;
}

template<typename T>
SList<T>::~SList()
{
    clear();
    delete head_;
    delete tail_;
}

template<typename T>
inline int SList<T>::size() const
{
    return size_;
}

template<typename T>
inline bool SList<T>::empty() const
{
    return size_ == 0;
}

template<typename T>
inline T &SList<T>::operator[](int r)
{
    assert(0 <= r);
    Node *p = first();
    while (r--) p = p->next_;
    return p->data_;
}

template<typename T>
inline const T &SList<T>::operator[](int r) const
{
    assert(0 <= r);
    Node *p = first();
    while (r--) p = p->next_;
    return p->data_;
}

template<typename T>
inline typename SList<T>::Node *SList<T>::first() const
{
    return head_->next_;
}

template<typename T>
inline typename SList<T>::Node *SList<T>::last() const
{
    return tail_->prev_;
}

template<typename T>
bool SList<T>::vaild(SList::Node *p) const
{
    Node *h = head_;
    while (h != tail_)
    {
        h = h->next_;
        if (p == h) return true;
    }
    return false;
}

template<typename T>
int SList<T>::disordered() const
{
    int s = 0;
    Node *p = first();
    while (p->next_ != tail_)
    {
        if (p->next_->data_ < p->data_) ++s;
        p = p->next_;
    }
    return s;
}

template<typename T>
typename SList<T>::Node *SList<T>::find(const T &e) const
{
    return find(e, size_, tail_);
}

template<typename T>
typename SList<T>::Node *SList<T>::find(const T &e, int n, SList::Node *p) const
{
    while (n-- && p != head_)
    {
        p = p->prev_;
        if (p->data_ == e) return p;
    }
    return nullptr;
}

template<typename T>
typename SList<T>::Node *SList<T>::search(const T &e) const
{
    return search(e, size_, tail_);
}

template<typename T>
typename SList<T>::Node *SList<T>::search(const T &e, int n, SList::Node *p) const
{
    while (0 <= n-- && p != head_)
    {
        p = p->prev_;
        if (p->data_ <= e) break;
    }
    return p;
}

template<typename T>
typename SList<T>::Node *SList<T>::selectMax(SList::Node *p, int n) const
{
    Node *max = p;
    while (--n)
    {
        p = p->next_;
//        this can be sure the algorithm stability
        if (max->data_ <= p->data_) max = p;
    }
    return max;
}

template<typename T>
typename SList<T>::Node *SList<T>::selectMax() const
{
    return selectMax(first(), size_);
}

template<typename T>
typename SList<T>::Node *SList<T>::insertAsFirst(const T &e)
{
    Node *node = new Node(e);
    node->next_ = head_->next_;
    head_->next_->prev_ = node;
    head_->next_ = node;
    node->prev_ = head_;
    ++size_;
    return node;
}

template<typename T>
typename SList<T>::Node *SList<T>::insertAsLast(const T &e)
{
    Node *node = new Node(e);
    tail_->prev_->next_ = node;
    node->prev_ = tail_->prev_;
    node->next_ = tail_;
    tail_->prev_ = node;
    ++size_;
    return node;
}

template<typename T>
typename SList<T>::Node *SList<T>::insertPrev(SList::Node *p, const T &e)
{
    Node *node = new Node(e);
    p->prev_->next_ = node;
    node->prev_ = p->prev_;
    node->next_ = p;
    p->prev_ = node;
    ++size_;
    return node;
}

template<typename T>
typename SList<T>::Node *SList<T>::insertSucc(SList::Node *p, const T &e)
{
    Node *node = new Node(e);
    p->next_->prev_ = node;
    node->next_ = p->next_;
    p->next_ = node;
    node->prev_ = p;
    ++size_;
    return node;
}

template<typename T>
T SList<T>::remove(SList::Node *p)
{
    auto t = p->data_;
    p->prev_->next_ = p->next_;
    p->next_->prev_ = p->prev_;
    delete p;
    --size_;
    return t;
}

template<typename T>
void SList<T>::clear()
{
    Node *p;
    while (size_-- && (p = head_->next_))
    {
        p->prev_->next_ = p->next_;
        p->next_->prev_ = p->prev_;
        delete p;
    }
    ++size_;
}

template<typename T>
void SList<T>::merge(SList &L)
{
    Node *p = first(), *q = L.first();
    while (p != tail_ && q != L.tail_)
    {
        if (p->data_ < q->data_) p = p->next_;
        else
        {
            insertPrev(p, q->data_);
            q = q->next_;
        }
    }
    while (q != L.tail_)
    {
        insertAsLast(q->data_);
        q = q->next_;
    }
}

template<typename T>
void SList<T>::selectSort(SList::Node *p, int n)
{
    Node *q, *pos = tail_;
    p = p->prev_;
    while (1 < n)
    {
        q = selectMax(p->next_, n--);
        q->prev_->next_ = q->next_;
        q->next_->prev_ = q->prev_;
        pos->prev_->next_ = q;
        q->prev_ = pos->prev_;
        q->next_ = pos;
        pos->prev_ = q;
        pos = pos->prev_;
    }
}

template<typename T>
void SList<T>::insertSort(SList::Node *p, int n)
{
    Node *q, *next = p;
    for (int r = 0; r < n; ++r)
    {
        q = search(p->data_, r, p);
        next = next->next_;
        p->prev_->next_ = p->next_;
        p->next_->prev_ = p->prev_;

        q->next_->prev_ = p;
        p->next_ = q->next_;

        q->next_ = p;
        p->prev_ = q;
        p = next;
    }
}

template<typename T>
void SList<T>::sort(SList::Node *p, int n)
{
    std::default_random_engine e(n);
    std::uniform_int_distribution<int> u;
    switch (u(e) % 2)
    {
        case 0:
            selectSort(p, n);
            break;
        case 1:
            insertSort(p, n);
            break;
    }
}

template<typename T>
void SList<T>::sort()
{
    sort(first(), size_);
}

template<typename T>
int SList<T>::deduplicate()
{
    auto oz = size();
    Node *p = first(), *q;
    int r = 0;
    while (p != tail_)
    {
        (q = find(p->data_, r, p)) ? remove(q) : ++r;
        p = p->next_;
    }
    return size_ - oz;
}

template<typename T>
int SList<T>::uniquify()
{
    if (size_ < 2) return 0;
    auto oz = size_;
    Node *p = first(), *q = nullptr;
    while (p != last())
    {
        q = p->next_;
        if (p->data_ == q->data_)
        {
            remove(q);
        }
        else p = q;
    }
    return size_ - oz;
}

template<typename T>
void SList<T>::reverse()
{
    if (size_ < 2) return;
    Node *p = first(), *q = p->prev_, *r = p->next_;
    while (p)
    {
        p->next_ = q;
        q->prev_ = p;

        q = p;
        p = r;
        r ? r = r->next_ : r;
    }
    tail_->prev_ = nullptr;
    head_->next_ = nullptr;
    auto t = tail_;
    tail_ = head_;
    head_ = t;
}

template<typename T>
void SList<T>::traverse(void (*pf)(T &))
{
    Node *p = first();
    while (p != tail_)
    {
        pf(p->data_);
        p = p->next_;
    }
}

template<typename T>
template<typename F>
void SList<T>::traverse(F f)
{
    Node *p = first();
    while (p != tail_)
    {
        f(p->data_);
        p = p->next_;
    }
}
}

#endif //TSINGHUA_DATASTRUCTURE_SLIST_H
