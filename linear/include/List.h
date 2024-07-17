//
// Created by shiqing on 19-5-23.
//

#ifndef TSINGHUA_DATASTRUCTURE_LIST_H
#define TSINGHUA_DATASTRUCTURE_LIST_H

#include <memory>
#include <assert.h>
#include <random>
#include <chrono>

namespace linear {
template<typename Tp>
struct ListNode
{
    Tp data_;
    ListNode *prev_;
    ListNode *next_;

    ListNode() : data_(), prev_(nullptr), next_(nullptr)
    {
    }

    template<typename... Args>
    ListNode(Args &&... args) : data_(std::forward<Args>(args)...), prev_(nullptr), next_(nullptr)
    {
    }
};

template<typename Tp>
struct ListIterator
{
    using Self = ListIterator<Tp>;
    using reference = Tp &;
    using pointer = Tp *;

    ListIterator() : node_()
    {
    }

    ListIterator(ListNode<Tp> *x) : node_(x)
    {
    }

    Self &operator++() noexcept
    {
        node_ = node_->next_;
        return *this;
    }

    Self &operator--() noexcept
    {
        node_ = node_->prev_;
        return *this;
    }

    Self operator++(int) noexcept
    {
        auto tmp = *this;
        node_ = node_->next_;
        return tmp;
    }

    Self operator--(int) noexcept
    {
        auto tmp = *this;
        node_ = node_->prev_;
        return tmp;
    }

    reference operator*() const noexcept
    {
        return node_->data_;
    }

    pointer operator->() const noexcept
    {
        return std::addressof(node_->data_);
    }

    bool operator==(const Self &rhs) const noexcept
    {
        return node_ == rhs.node_;
    }

    bool operator!=(const Self &rhs) const noexcept
    {
        return node_ != rhs.node_;
    }

    explicit operator ListNode<Tp> *() const noexcept
    {
        return node_;
    }

private:
    ListNode<Tp> *node_;
};

template<typename T>
inline bool operator==(const ListIterator<T> &lhs, const ListIterator<T> &rhs) noexcept
{
    return lhs.operator==(rhs);
}

template<typename T>
inline bool operator!=(const ListIterator<T> &lhs, const ListIterator<T> &rhs) noexcept
{
    return lhs.operator!=(rhs);
}

template<typename>
class List;

template<typename T>
bool operator==(const List<T> &lhs, const List<T> &rhs);

template<typename T>
bool operator!=(const List<T> &lhs, const List<T> &rhs);

template<typename T>
std::ostream &operator<<(std::ostream &os, const List<T> &rhs);

template<typename T>
class List
{
    friend bool operator==<T>(const List &lhs, const List &rhs);

    friend bool operator!=<T>(const List &lhs, const List &rhs);

    friend std::ostream &operator
    <<<T>(
    std::ostream &os,
    const List &rhs
    );

public:
    using Node = ListNode<T>;
    using Iterator = ListIterator<T>;
    using ConstIterator = const ListIterator<T>;
    using ValueType = T;

    List()
    {
        init();
    }

    /**
     *
     * @param n This constructor fills the List with @a __n default constructed elements.
     */
    explicit List(long n);

    List(long n, const ValueType &val);

    List(std::initializer_list<ValueType> li);

    template<typename InIterator,
            typename = std::_RequireInputIter<InIterator>>
    List(InIterator beg, InIterator end);

    List(const List &rhs);

    List(List &&rhs) noexcept;

    List &operator=(const List &rhs) &;

    List &operator=(List &&rhs) &;

    virtual ~List()
    {
        clear();
        /*
         * Members of an object are destroyed when the object of which they are a part is destroyed.
         * Dynamically allocated objects are destroyed when the delete operator is applied to a pointer to the object
         */
        delete head_;
        delete tail_;

    }

    Iterator begin() noexcept
    {
        return Iterator(head_->next_);
    }

    ConstIterator begin() const noexcept
    {
        return Iterator(head_->next_);
    }

    Iterator end() noexcept
    {
        return Iterator(tail_);
    }

    ConstIterator end() const noexcept
    {
        return Iterator(tail_);
    }

    bool empty() const noexcept
    {
        return head_->next_ == tail_;
    }

    long size() const noexcept
    {
        return sizeCnt_;
    }

    /*
    * This function will %resize the %list to the specified number
    * of elements.  If the number is smaller than the %list's
    * current size the %list is truncated, otherwise default
    * constructed elements are appended
    */
    void resize(long newSize);

    T &front() const noexcept
    {
        return *begin();
    }

    T &back() const noexcept
    {
        auto tmp = end();
        return *--tmp;
    }

    void pushFront(const ValueType &val);

    void pushFront(ValueType &&x);

    void popFront() noexcept;

    void pushBack(const ValueType &val);

    void pushBack(ValueType &&x);

    void popBack() noexcept;

    Iterator insert(Iterator pos, const ValueType &val);

    Iterator insert(Iterator pos, ValueType &&x);

    Iterator insert(Iterator pos, long n, const ValueType &val);

    Iterator insert(Iterator pos, std::initializer_list<ValueType> li);

    template<typename InIterator,
            typename = std::_RequireInputIter<InIterator>>
    Iterator insert(Iterator pos, InIterator beg, InIterator end);

    Iterator erase(Iterator pos) noexcept;

    Iterator erase(Iterator first, Iterator last);

    void clear() noexcept;

    void remove(const ValueType &val);

    template<typename Predicate>
    void removeIf(Predicate predicate);

    /*
     * alg.
     */

    Iterator find(const ValueType &val) const noexcept;

    Iterator search(const ValueType &val) const noexcept;

    Iterator selectMax() const noexcept;

    void merge(List &rhs);

    void sort();

    long deduplicate();

    long uniquely();

    void reverse();

protected:
    /*
     * return the first element is bigger than val.
     */
    Node *search(Node *p, const ValueType &val) const noexcept;

    void selectSort() noexcept;

    void mergeSort() noexcept;

    void insertSort() noexcept;

private:
    Node *head_, *tail_;
    long sizeCnt_ = 0L;

    void init() noexcept
    {
        head_ = new Node, tail_ = new Node;
        head_->prev_ = nullptr;
        head_->next_ = tail_;
        tail_->prev_ = head_;
        tail_->next_ = nullptr;
        sizeCnt_ = 0L;
    }
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const List<T> &rhs)
{
    for (auto it = rhs.begin(); it != rhs.end(); ++it)
    {
        os << *it << " ";
    }
    return os;
}

template<typename T>
bool operator==(const List<T> &lhs, const List<T> &rhs)
{
    if (lhs.sizeCnt_ != rhs.sizeCnt_) return false;
    auto lIt = lhs.begin(), rIt = rhs.end();
    while (lIt != lhs.end())
    {
        if (*lIt != *rIt) return false;
        ++lIt, ++rIt;
    }
    return true;
}

template<typename T>
bool operator!=(const List<T> &lhs, const List<T> &rhs)
{
    return !(lhs == rhs);
}

namespace UtilityL {

template<typename T> using Node = ListNode<T>;

template<typename T>
void createNodesByValue(long n, Node<T> *head, Node<T> *tail, const T &val = T())
{
    assert(n > 0);
    Node<T> *curr = head, *next;
    while (n--)
    {
        next = new Node<T>(val);
        curr->next_ = next;
        next->prev_ = curr;
        curr = next;
    }
    curr->next_ = tail;
    tail->prev_ = curr;
}

template<typename T, typename InIterator>
long createListByRange(InIterator beg, InIterator end, Node<T> *head, Node<T> *tail)
{
    long cnt = 0;
    Node<T> *curr = head, *next;
    while (beg != end)
    {
        next = new Node<T>(*beg++);
        curr->next_ = next;
        next->prev_ = curr;
        curr = next;
        ++cnt;
    }
    curr->next_ = tail;
    tail->prev_ = curr;
    return cnt;
}

template<typename T>
inline void destroyAt(Node<T> *&p)
{
    delete p;
}

}

template<typename T>
List<T>::List(long n) : List()
{
    UtilityL::createNodesByValue(n, head_, tail_);
    sizeCnt_ = n;
}

template<typename T>
List<T>::List(long n, const ValueType &val) : List()
{
    UtilityL::createNodesByValue(n, head_, tail_, val);
    sizeCnt_ = n;
}

template<typename T>
List<T>::List(std::initializer_list<ValueType> li) : List()
{
    auto cnt = UtilityL::createListByRange(li.begin(), li.end(), head_, tail_);
    sizeCnt_ = cnt;
}

template<typename T>
template<typename InIterator, typename>
List<T>::List(InIterator beg, InIterator end) : List()
{
    auto cnt = UtilityL::createListByRange(beg, end, head_, tail_);
    sizeCnt_ = cnt;
}

template<typename T>
List<T>::List(const List &rhs) : List()
{
    auto cnt = UtilityL::createListByRange(rhs.begin(), rhs.end(), head_, tail_);
    sizeCnt_ = cnt;
}

template<typename T>
List<T>::List(List &&rhs) noexcept : head_(rhs.head_), tail_(rhs.tail_), sizeCnt_(rhs.sizeCnt_)
{
    rhs.head_ = nullptr;
    rhs.tail_ = nullptr;
}

template<typename T>
List<T> &List<T>::operator=(const List &rhs) &
{
    if (this != &rhs)
    {
        clear();
        sizeCnt_ = UtilityL::createListByRange(rhs.begin(), rhs.end(), head_, tail_);
    }
    return *this;
}

template<typename T>
List<T> &List<T>::operator=(List &&rhs) &
{
    if (this == &rhs) return *this;
    this->~List();
    head_ = rhs.head_;
    tail_ = rhs.tail_;
    sizeCnt_ = rhs.sizeCnt_;
    rhs.head_ = rhs.tail_ = nullptr;
    return *this;
}

template<typename T>
void List<T>::resize(long newSize)
{
    long n = sizeCnt_ - newSize;
    if (n == 0) return;
    if (n < 0)
    {
        n = -n;
        while (n--) pushBack(T());
    }
    else
    {
        auto it = begin();
        n = newSize;
        while (n--) ++it;
        erase(it, end());
    }
}

template<typename T>
void List<T>::pushFront(const ValueType &val)
{
    auto node = new Node(val);
    auto hook = head_->next_;
    head_->next_ = node;
    node->prev_ = head_;
    node->next_ = hook;
    hook->prev_ = node;
    ++sizeCnt_;
}

template<typename T>
void List<T>::pushFront(ValueType &&x)
{
    auto node = new Node(std::move(x));
    auto hook = head_->next_;
    head_->next_ = node;
    node->prev_ = head_;
    node->next_ = hook;
    hook->prev_ = node;
    sizeCnt_++;
}

template<typename T>
void List<T>::popFront() noexcept
{
    if (sizeCnt_ > 0)
    {
        auto first = head_->next_;
        head_->next_ = first->next_;
        first->next_->prev_ = head_;
        UtilityL::destroyAt(first);
        --sizeCnt_;
    }
}

template<typename T>
void List<T>::pushBack(const ValueType &val)
{
    auto last = tail_->prev_;
    auto node = new Node(val);
    last->next_ = node;
    node->prev_ = last;
    node->next_ = tail_;
    tail_->prev_ = node;
    ++sizeCnt_;
}

template<typename T>
void List<T>::pushBack(ValueType &&x)
{
    auto last = tail_->prev_;
    auto node = new Node(std::move(x));
    last->next_ = node;
    node->prev_ = last;
    node->next_ = tail_;
    tail_->prev_ = node;
    ++sizeCnt_;
}

template<typename T>
void List<T>::popBack() noexcept
{
    if (sizeCnt_ > 0)
    {
        auto last = tail_->prev_;
        last->prev_->next_ = tail_;
        tail_->prev_ = last->prev_;
        UtilityL::destroyAt(last);
        --sizeCnt_;
    }
}

template<typename T>
typename List<T>::Iterator List<T>::insert(List::Iterator pos, const ValueType &val)
{
    Node *curr = static_cast<Node *>(pos), *pre = curr->prev_;
    auto node = new Node(val);
    pre->next_ = node;
    node->prev_ = pre;
    node->next_ = curr;
    curr->prev_ = node;
    ++sizeCnt_;
    return node;
}

template<typename T>
typename List<T>::Iterator List<T>::insert(List::Iterator pos, ValueType &&x)
{
    Node *curr = static_cast<Node *>(pos), *pre = curr->prev_;
    auto node = new Node(std::move(x));
    pre->next_ = node;
    node->prev_ = pre;
    node->next_ = curr;
    curr->prev_ = node;
    ++sizeCnt_;
    return node;
}

template<typename T>
typename List<T>::Iterator List<T>::insert(List::Iterator pos, long n, const ValueType &val)
{
    Node *last = static_cast<Node *>(pos), *curr = last->prev_, *next;
    while (n--)
    {
        next = new Node(val);
        curr->next_ = next;
        next->prev_ = curr;
        curr = next;
    }
    curr->next_ = last;
    last->prev_ = curr;
    sizeCnt_ += n;
    return curr;
}

template<typename T>
typename List<T>::Iterator List<T>::insert(List::Iterator pos, std::initializer_list<ValueType> li)
{
    return insert(pos, li.begin(), li.end());
}

template<typename T>
template<typename InIterator, typename>
typename List<T>::Iterator List<T>::insert(List::Iterator pos, InIterator beg, InIterator end)
{
    Node *last = static_cast<Node *>(pos), *curr = last->prev_, *next;
    while (beg != end)
    {
        next = new Node(*beg++);
        curr->next_ = next;
        next->prev_ = curr;
        curr = next;
        ++sizeCnt_;
    }
    curr->next_ = last;
    last->prev_ = curr;
    return curr;
}

template<typename T>
typename List<T>::Iterator List<T>::erase(List::Iterator pos) noexcept
{
    Iterator r = pos;
    if (pos != head_ && pos != tail_)
    {
        Node *del = static_cast<Node *>(pos), *prev = del->prev_;
        prev->next_ = del->next_;
        del->next_->prev_ = prev;
        UtilityL::destroyAt(del);
        --sizeCnt_;
        r = prev->next_;
    }
    return r;
}

template<typename T>
typename List<T>::Iterator List<T>::erase(List::Iterator first, List::Iterator last)
{
    Iterator pos = first;
    --pos;
    while (first != last)
    {
        Node *curr = static_cast<Node *>(first), *pre = curr->prev_;
        ++first;
        pre->next_ = curr->next_;
        curr->next_->prev_ = pre;
        UtilityL::destroyAt(curr);
        --sizeCnt_;
    }
    return ++pos;
}

template<typename T>
void List<T>::clear() noexcept
{
    if (head_ && tail_)
    {
        Node *curr = head_->next_, *next;
        while (curr != tail_)
        {
            next = curr->next_;
            UtilityL::destroyAt(curr);
            curr = next;
        }
        head_->next_ = curr;
        curr->prev_ = head_;
        sizeCnt_ = 0L;
    }
}

/*
 * alg.
 */


template<typename T>
void List<T>::remove(const ValueType &val)
{
    auto pos = find(val);
    erase(pos);
}

template<typename T>
template<typename Predicate>
void List<T>::removeIf(Predicate predicate)
{
    auto it = begin();
    while (it != end())
    {
        if (predicate(*it))
        {
            it = erase(it);
        }
        else
        {
            ++it;
        }
    }
}

template<typename T>
typename List<T>::Iterator List<T>::find(const ValueType &val) const noexcept
{
    for (auto it = begin(); it != end(); ++it)
    {
        if (*it == val)
        {
            return it;
        }
    }
    return end();
}

template<typename T>
typename List<T>::Node *List<T>::search(List::Node *p, const ValueType &val) const noexcept
{
    Node *curr = p->prev_;
    while (curr != head_)
    {
        if (curr->data_ <= val)
        {
            break;
        }
        curr = curr->prev_;
    }
    return curr->next_;
}

/*
 * return the last of element is not bigger than val.
 */
template<typename T>
typename List<T>::Iterator List<T>::search(const ValueType &val) const noexcept
{
    auto p = search(tail_, val);
    return p->prev_;
}

namespace HelpL {
template<typename T> using Node = ListNode<T>;

template<typename T>
Node<T> *selectMax(Node<T> *head, Node<T> *p) noexcept
{
    Node<T> *curr = head->next_, *maxIt = curr;
    while (curr != p)
    {
        if (maxIt->data_ < curr->data_)
        {
            maxIt = curr;
        }
        curr = curr->next_;
    }
    return maxIt;
}

template<typename T>
void merge(Node<T> *&p, long n, Node<T> *q, long m, List<T> &L)
{
    auto pp = p->prev_;
    while (m > 0)
    {
        if (n > 0 && p->data_ <= q->data_)
        {
            p = p->next_;
            if (q == p) break;
            --n;
        }
        else
        {
            L.insert(p, q->data_);
            L.erase((q = q->next_)->prev_);
            --m;
        }
    }
    p = pp->next_;
}

template<typename T>
void mergeSort(Node<T> *&p, long n, List<T> &L)
{
    if (n < 2) return;
    int m = n / 2;
    Node<T> *q = p;
    for (long i = 0; i < m; ++i) q = q->next_;
    mergeSort(p, m, L);
    mergeSort(q, n - m, L);
    merge(p, m, q, n - m, L);
}

template<typename T>
Node<T> *find(Node<T> *head, Node<T> *p, const T &val)
{
    auto q = p->prev_;
    while (q != head)
    {
        if (q->data_ == val) break;
        q = q->prev_;
    }
    return q;
}

}

template<typename T>
typename List<T>::Iterator List<T>::selectMax() const noexcept
{
    return HelpL::selectMax(head_, tail_);
}

template<typename T>
void List<T>::merge(List &rhs)
{
    for (Node *p = head_->next_, *q = rhs.head_->next_; p != tail_ || q != rhs.tail_;)
    {
        if (p == tail_) sizeCnt_ = UtilityL::createListByRange(rhs.begin(), rhs.end(), head_, tail_);
        if (q == rhs.tail_) return;
        if (p->data_ <= q->data_) p = p->next_;
        else
        {
            insert(p, q->data_);
            q = q->next_;
        }
        if (q == rhs.tail_ && p != tail_) break;
        while (p == tail_ && q != rhs.tail_)
        {
            insert(p, q->data_);
            q = q->next_;
        }
    }
}

template<typename T>
void List<T>::selectSort() noexcept
{
    Node *q = tail_;
    while (q != head_->next_)
    {
        auto p = HelpL::selectMax(head_, q);
        q = static_cast<Node *>(insert(q, p->data_));
        erase(p);
    }
}

template<typename T>
void List<T>::mergeSort() noexcept
{
    HelpL::mergeSort(head_->next_, size(), *this);
}

template<typename T>
void List<T>::insertSort() noexcept
{
    auto p = head_->next_->next_;
    while (p && p != tail_)
    {
        auto sp = search(p, p->data_);
        if (sp == p) p = p->next_;
        else
        {
            insert(sp, p->data_);
            p = static_cast<Node *>(erase(p));
        }
    }
}

template<typename T>
void List<T>::sort()
{
    static std::default_random_engine e(std::chrono::system_clock::now().time_since_epoch().count());
    static std::uniform_int_distribution<int> u(0, 2);
    switch (u(e))
    {
        case 0:
            insertSort();
            break;
        case 1:
            selectSort();
            break;
        case 2:
            mergeSort();
            break;
    }
}

template<typename T>
long List<T>::deduplicate()
{
    long cnt = 0;
    auto p = head_->next_;
    while (p != tail_)
    {
        auto it = HelpL::find(head_, p, p->data_);
        if (it == head_) p = p->next_;
        else
        {
            p = static_cast<Node *>(erase(p));
            ++cnt;
        }
    }
    return cnt;
}

template<typename T>
long List<T>::uniquely()
{
    auto p = head_->next_, q = p->next_;
    long n = 1;
    while (q && q != tail_)
    {
        if (q->data_ != p->data_)
        {
            p = p->next_;
            ++n;
            if (p != q) p->data_ = q->data_;
        }
        q = q->next_;
    }
    long sz = size();
    resize(n);
    return sz - n;
}

template<typename T>
void List<T>::reverse()
{
    if (size() < 2) return;
    Node *p = head_, *curr = p->next_, *next;
    while (curr)
    {
        next = curr->next_;
        curr->next_ = p;
        p->prev_ = curr;
        p = curr;
        curr = next;
    }
    tail_->prev_ = nullptr;
    head_->next_ = nullptr;
    auto newHead = head_;
    head_ = tail_;
    tail_ = newHead;
}

}

#endif //TSINGHUA_DATASTRUCTURE_LIST_H
