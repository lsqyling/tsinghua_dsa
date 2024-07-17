//
// Created by shiqing on 2020/5/25.
//

#ifndef TSINGHUA_DATASTRUCTURE_BINARY_TREE_H
#define TSINGHUA_DATASTRUCTURE_BINARY_TREE_H

#include <algorithm>
#include "tree_node.h"
#include "../../part_1_linear/include/stack_queue.h"

namespace tree {
template<typename T>
class BinaryTree
{
public:
    using Node = BinaryTreeNode<T>;

    BinaryTree();

    template<int N>
    BinaryTree(const T (&pre_sequence)[N], const T (&in_sequence)[N]);

    virtual ~BinaryTree();

    int size() const;

    bool empty() const;

    Node *root() const;

    Node *insertAsRoot(const T &e);

    Node *insertAsLC(Node *x, const T &e);

    Node *insertAsRC(Node *x, const T &e);

    Node *attachAsLC(Node *x, BinaryTree *&t);

    Node *attachAsRC(Node *x, BinaryTree *&t);

    int remove(Node *x);

    BinaryTree *separateFrom(Node *x);

    template<typename F>
    void traversalLevel(F f);

    template<typename F>
    void traversalPre(F f);

    template<typename F>
    void traversalIn(F f);

    template<typename F>
    void traversalPost(F f);

protected:
    virtual int updateHeight(Node *x);

    void updateHeightAbove(Node *x);

    int destroy(Node *p);

    Node *create(const T *preArr, int preL, int preR, const T *inArr, int inL, int inR);

    int size_;
    Node *root_;
};

template<typename T>
BinaryTree<T>::BinaryTree() : size_(0), root_(nullptr)
{
}

template<typename T>
template<int N>
BinaryTree<T>::BinaryTree(const T (&pre_sequence)[N], const T (&in_sequence)[N])
{
    root_ = create(pre_sequence, 0, N - 1, in_sequence, 0, N - 1);
    size_ = N;
}


template<typename T>
BinaryTree<T>::~BinaryTree()
{
    destroy(root_);
    root_ = nullptr;
}

template<typename T>
inline int BinaryTree<T>::size() const
{
    return size_;
}

template<typename T>
inline bool BinaryTree<T>::empty() const
{
    return size_ == 0;
}

template<typename T>
inline typename BinaryTree<T>::Node *BinaryTree<T>::root() const
{
    return root_;
}

template<typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::insertAsRoot(const T &e)
{
    ++size_;
    return root_ = new Node(e);
}

template<typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::insertAsLC(Node *x, const T &e)
{
    ++size_;
    x->insertAsLeftChild(e);
    updateHeightAbove(x);
    return x->left_;
}

template<typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::insertAsRC(Node *x, const T &e)
{
    ++size_;
    x->insertAsRightChild(e);
    updateHeightAbove(x);
    return x->right_;
}

template<typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::attachAsLC(Node *x, BinaryTree *&t)
{
    x->left_ = t->root_;
    if (x->left_) x->left_->parent_ = x;
    updateHeightAbove(x);
    size_ += t->size_;
    t->root_ = nullptr;
    t->size_ = 0;
    return x->left_;
}

template<typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::attachAsRC(Node *x, BinaryTree *&t)
{
    x->right_ = t->root_;
    if (x->right_) x->right_->parent_ = x;
    updateHeightAbove(x);
    size_ += t->size_;
    t->root_ = nullptr;
    t->size_ = 0;
    return x->right_;
}

template<typename T>
int BinaryTree<T>::remove(BinaryTree::Node *x)
{
    fromParentToPointer(x) = nullptr;
    updateHeightAbove(x->parent_);
    int n = destroy(x);
    size_ -= n;
    return n;
}

template<typename T>
BinaryTree<T> *BinaryTree<T>::separateFrom(BinaryTree::Node *x)
{
    fromParentToPointer(x) = nullptr;
    updateHeightAbove(x->parent_);
    auto *tree = new BinaryTree<T>;
    tree->root_ = x;
    x->parent_ = nullptr;
    tree->size_ = x->size();
    size_ -= x->size();
    return tree;
}

template<typename T>
template<typename F>
void BinaryTree<T>::traversalLevel(F f)
{
    if (root_) root_->traversalLevel(f);
}

template<typename T>
template<typename F>
void BinaryTree<T>::traversalPre(F f)
{
    if (root_) root_->traversalPre(f);
}

template<typename T>
template<typename F>
void BinaryTree<T>::traversalIn(F f)
{
    if (root_) root_->traversalIn(f);
}

template<typename T>
template<typename F>
void BinaryTree<T>::traversalPost(F f)
{
    if (root_) root_->traversalPost(f);
}

template<typename T>
inline int BinaryTree<T>::updateHeight(Node *x)
{
    return x->height_ = 1 +
                        std::max(stature(x->left_), stature(x->right_));
}

template<typename T>
void BinaryTree<T>::updateHeightAbove(Node *x)
{
    while (x)
    {
        updateHeight(x);
        x = x->parent_;
    }
}

template<typename T>
int BinaryTree<T>::destroy(Node *p)
{
    if (!p) return 0;
    int n = 1 + destroy(p->left_) + destroy(p->right_);
    delete p;
    return n;
}

template<typename T>
BinaryTreeNode <T> *BinaryTree<T>::create(const T *preArr, int preL, int preR, const T *inArr, int inL, int inR)
{
    if (preL > preR) return nullptr;
    Node *root = new Node(preArr[preL]);
    int k;
    for (k = inL; k <= inR; ++k)
    {
        if (inArr[k] == preArr[preL]) break;
    }
    int num_left = k - inL;
    Node *left = create(preArr, preL + 1, preL + num_left, inArr, inL, k - 1);
    root->left_ = left;
    if (left) left->parent_ = root;
    Node *right = create(preArr, preL + num_left + 1, preR, inArr, k + 1, inR);
    root->right_ = right;
    if (right) right->parent_ = root;
    return root;
}
}


#endif //TSINGHUA_DATASTRUCTURE_BINARY_TREE_H
