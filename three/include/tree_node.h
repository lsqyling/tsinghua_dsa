//
// Created by shiqing on 2020/5/25.
//

#ifndef TSINGHUA_DATASTRUCTURE_BINARY_TREE_NODE_H
#define TSINGHUA_DATASTRUCTURE_BINARY_TREE_NODE_H

#include <utility>
#include "../../part_1_linear/include/stack_queue.h"

namespace tree {
template<typename T>
struct BinaryTreeNode
{
    using Node = BinaryTreeNode<T>;

    template<typename ...Args>
    explicit BinaryTreeNode(Args &&...params)
            : data_(std::forward<Args>(params)...), height_(0),
              parent_(nullptr),
              left_(nullptr), right_(nullptr)
    {
    }

    BinaryTreeNode(const T &e, BinaryTreeNode *p)
            : data_(e), height_(0),
              parent_(p),
              left_(nullptr), right_(nullptr)
    {
    }

    BinaryTreeNode *insertAsLeftChild(const T &e);

    BinaryTreeNode *insertAsRightChild(const T &e);

    BinaryTreeNode *succ();

    int size() const;

    template<typename F>
    void traversalLevel(F f);

    template<typename F>
    void traversalPre(F f);

    template<typename F>
    void traversalIn(F f);

    template<typename F>
    void traversalPost(F f);


    T data_;
    int height_;
    BinaryTreeNode *parent_;
    BinaryTreeNode *left_, *right_;

};

template<typename T> using Node = BinaryTreeNode<T>;


template<typename T>
inline int stature(BinaryTreeNode<T> *p)
{
    return p ? p->height_ : -1;
}

template<typename T>
inline BinaryTreeNode<T> *&fromParentToPointer(BinaryTreeNode<T> *p)
{
    return p->parent_->left_ == p ? p->parent_->left_ : p->parent_->right_;
}

template<typename T>
inline bool isRChild(BinaryTreeNode<T> *p)
{
    return p->parent_ ? p->parent_->right_ == p : false;
}

template<typename T>
inline bool isLChild(BinaryTreeNode<T> *p)
{
    return p->parent_ ? p->parent_->left_ == p : false;
}


template<typename T>
int BinaryTreeNode<T>::size() const
{
    int s = 1;
    if (left_) s += left_->size();
    if (right_) s += right_->size();
    return s;
}

template<typename T>
inline BinaryTreeNode<T> *BinaryTreeNode<T>::insertAsLeftChild(const T &e)
{
    return left_ = new BinaryTreeNode<T>(e, this);
}

template<typename T>
inline BinaryTreeNode<T> *BinaryTreeNode<T>::insertAsRightChild(const T &e)
{
    return right_ = new BinaryTreeNode<T>(e, this);
}

template<typename T>
BinaryTreeNode<T> *BinaryTreeNode<T>::succ()
{
    Node *p = this;
    if (p->right_)
    {
        p = p->right_;
        while (p->left_) p = p->left_;
    }
    else
    {
        while (isRChild(p)) p = p->parent_;
        p = p->parent_;
    }
    return p;
}


template<typename T>
template<typename F>
void BinaryTreeNode<T>::traversalLevel(F f)
{
    Node *p = this;
    linear::queue<Node *> Q;
    Node *flag = new Node;
    Q.enqueue(p);
    Q.enqueue(flag);
    while (!Q.empty())
    {
        Node *front = Q.dequeue();
        if (front == flag)
        {
            printf("\n");
            if (!Q.empty()) Q.enqueue(flag);
        }
        else
        {
            f(front);
            if (front->left_) Q.enqueue(front->left_);
            if (front->right_) Q.enqueue(front->right_);
        }
    }
}

template<typename T>
template<typename F>
void BinaryTreeNode<T>::traversalPre(F f)
{
    Node *p = this;
    linear::stack<Node *> S;
    while (!S.empty() || p)
    {
        while (p)
        {
            S.push(p);
            f(p);
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
void BinaryTreeNode<T>::traversalIn(F f)
{
    Node *p = this;
    linear::stack<Node *> S;
    while (!S.empty() || p)
    {
        while (p)
        {
            S.push(p);
            p = p->left_;
        }
        if (!S.empty())
        {
            p = S.pop();
            f(p);
            p = p->right_;
        }
    }
}

template<typename T>
template<typename F>
void BinaryTreeNode<T>::traversalPost(F f)
{
    Node *p = this, *r = nullptr;
    linear::stack<Node *> S;
    while (!S.empty() || p)
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
                f(p);
                r = p, p = nullptr;
            }
        }
    }
}
}


#endif //TSINGHUA_DATASTRUCTURE_BINARY_TREE_NODE_H
