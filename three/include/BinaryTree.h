//
// Created by shiqing on 19-7-13.
//

#ifndef TSINGHUA_DATASTRUCTURE_BINARYTREE_H
#define TSINGHUA_DATASTRUCTURE_BINARYTREE_H

#include <utility>
#include "../../part_1_linear/include/Stack.h"
#include "../../part_1_linear/include/Queue.h"

namespace tree {

template<typename T>
struct BinaryTreeNode
{
    template<typename... Args>
    explicit BinaryTreeNode(Args &&...args)
            : val_(std::forward<Args>(args)...), parent_(nullptr), left_(nullptr), right_(nullptr)
    {
        static_assert(
                std::is_constructible<T, Args...>::value,
                "Parameter args... can't be used to construct a T"
        );
    }

    T val_;
    BinaryTreeNode *parent_;
    BinaryTreeNode *left_;
    BinaryTreeNode *right_;
};

template<typename T>
struct Visit
{
    void operator()(T *p) const
    {
        cout << p->val_ << " ";
    }
};

template<typename T>
class BinaryTree
{
public:
    using Node = BinaryTreeNode<T>;

    BinaryTree() : root_(nullptr)
    {
    }

    template<unsigned N>
    BinaryTree(const T (&preArr)[N], const T (&inArr)[N]);

    BinaryTree(const BinaryTree &rhs);

    BinaryTree &operator=(const BinaryTree &rhs);

    BinaryTree(BinaryTree &&rhs) noexcept;

    BinaryTree &operator=(BinaryTree &&rhs) noexcept;

    int height() const;

    int size() const;

    bool empty() const
    {
        return root_ == nullptr;
    }

    /*
     * traversal algorithm.
     */
    template<typename F = Visit<Node>>
    void preOrderTraversal(F visit = F());

    template<typename F = Visit<Node>>
    void inOrderTraversal(F visit = F());

    template<typename F = Visit<Node>>
    void postOrderTraversal(F visit = F());

    template<typename F = Visit<Node>>
    void levelOrderTraversal(F visit = F());

    ~BinaryTree() noexcept
    {
        destroy(root_);
        root_ = nullptr;
    }

private:
    void destroy(Node *p)
    {
        if (p)
        {
            destroy(p->left_);
            destroy(p->right_);
            delete p;
        }
    }

    Node *deepCopy(Node *p);

private:
    Node *root_;

};

template<typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::deepCopy(BinaryTree::Node *p)
{
    if (p == nullptr) return nullptr;
    Node *pLeft = deepCopy(p->left_),
            *pRight = deepCopy(p->right_);
    auto r = new Node(p->val_);
    r->left_ = pLeft;
    r->right_ = pRight;
    return r;
}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree &rhs)
{
    root_ = deepCopy(rhs.root_);
}

template<typename T>
BinaryTree<T> &BinaryTree<T>::operator=(const BinaryTree &rhs)
{
    if (this != &rhs)
    {
        root_ = deepCopy(rhs.root_);
    }
    return *this;
}

template<typename T>
BinaryTree<T>::BinaryTree(BinaryTree &&rhs) noexcept : root_(rhs.root_)
{
    rhs.root_ = nullptr;
}

template<typename T>
BinaryTree<T> &BinaryTree<T>::operator=(BinaryTree &&rhs) noexcept
{
    if (this != &rhs)
    {
        root_ = rhs.root_;
        rhs.root_ = nullptr;
    }
    return *this;
}

template<typename T>
typename BinaryTree<T>::Node *constructByPreorderAndInOrder(const T *pre, int b, int e, const T *in, int lo, int hi)
{
    if (b == e || lo == hi) return nullptr;
    auto &val = pre[b];
    auto root = new BinaryTreeNode<T>(val);

    if (b + 1 == e && lo + 1 == hi) return root;

    int i = lo;
    while (i < hi && in[i] != val) ++i;

    int nLeft = i - lo;
    int nRight = hi - i - 1;

    if (nLeft)
    {
        root->left_ = constructByPreorderAndInOrder(pre, b + 1, b + 1 + nLeft, in, lo, i);
    }

    if (nRight)
    {
        root->right_ = constructByPreorderAndInOrder(pre, e - nRight, e, in, i + 1, hi);
    }
    return root;
}

template<typename T>
template<unsigned int N>
BinaryTree<T>::BinaryTree(const T (&preArr)[N], const T (&inArr)[N])
{
    root_ = constructByPreorderAndInOrder(preArr, 0, N, inArr, 0, N);
}

template<typename Node>
int recursiveHeight(Node *p)
{
    if (p == nullptr) return 0;
    if (p->left_ == nullptr
        && p->right_ == nullptr)
        return 1;

    return std::max(recursiveHeight(p->left_), recursiveHeight(p->right_)) + 1;
}

template<typename T>
int BinaryTree<T>::height() const
{
    return recursiveHeight(root_);
}

template<typename T>
int BinaryTree<T>::size() const
{
    auto p = root_;
    linear::Stack<Node *> S;
    int cnt = 0;
    while (p || !S.empty())
    {

        while (p)
        {
            S.push(p);
            ++cnt;
            p = p->left_;
        }

        if (!S.empty())
        {
            p = S.pop();
            p = p->right_;
        }
    }

    return cnt;
}

template<typename T>
template<typename F>
void BinaryTree<T>::preOrderTraversal(F visit)
{
    Node *p = root_;
    linear::Stack<Node *> S;

    while (p || !S.empty())
    {

        while (p)
        {
            S.push(p);
            visit(p);
            p = p->left_;
        }

        if (!S.empty())
        {
            p = S.pop();
            p = p->right_;
        }

    }

}

template<typename T>
template<typename F>
void BinaryTree<T>::inOrderTraversal(F visit)
{
    auto p = root_;
    linear::Stack<Node *> S;

    while (p || !S.empty())
    {

        while (p)
        {
            S.push(p);
            p = p->left_;
        }

        if (!S.empty())
        {
            p = S.pop();
            visit(p);
            p = p->right_;
        }

    }
}

template<typename T>
template<typename F>
void BinaryTree<T>::postOrderTraversal(F visit)
{
    Node *p = root_, *r = nullptr;
    linear::Stack<Node *> S;

    while (p || !S.empty())
    {

        while (p)
        {
            S.push(p);
            p = p->left_;
        }

        if (!S.empty())
        {
            p = S.top();

            if (p->right_ && p->right_ != r)
            {
                p = p->right_;
            }
            else
            {
                S.pop();
                visit(p);
                r = p, p = nullptr;
            }
        }
    }
}

template<typename T>
template<typename F>
void BinaryTree<T>::levelOrderTraversal(F visit)
{
    if (root_ == nullptr) return;
    Node *p = root_, *q = nullptr;
    linear::Queue<Node *> Q;
    auto flagNode = new Node;
    Q.enqueue(p);
    Q.enqueue(flagNode);

    while (!Q.empty())
    {

        p = Q.dequeue();
        q = Q.front();
        visit(p);

        if (q == flagNode)
        {
            Q.dequeue();
            cout << '\n';
            if (p->left_) Q.enqueue(p->left_);
            if (p->right_) Q.enqueue(p->right_);

            if (!Q.empty())
            {
                Q.enqueue(flagNode);
            }
        }
        else
        {
            if (p->left_) Q.enqueue(p->left_);
            if (p->right_) Q.enqueue(p->right_);
        }

    }
}

}

#endif //TSINGHUA_DATASTRUCTURE_BINARYTREE_H
