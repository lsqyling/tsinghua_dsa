//
// Created by shiqing on 19-8-3.
//

#ifndef TSINGHUA_DATASTRUCTURE_AVLTREE_H
#define TSINGHUA_DATASTRUCTURE_AVLTREE_H

#include "../../common/CommonHeaders.h"
#include "../../part_1_linear/include/Stack.h"
#include "../../part_1_linear/include/Queue.h"

namespace tree {


template<typename K, typename V>
struct AVLNode
{
    AVLNode(const K &key, AVLNode *parent)
            : data_(key, V()),
              height_(1),
              parent_(parent), left_(nullptr), right_(nullptr)
    {
    }

    explicit AVLNode(const K &key, const V &val = V(), AVLNode *parent = nullptr)
            : data_(key, val),
              height_(1),
              parent_(parent), left_(nullptr), right_(nullptr)
    {

    }

    struct Pair
    {
        Pair(const K &key, const V &val) : key_(key), value_(val)
        {
        }

        K key_;
        V value_;
    };

    Pair data_;
    int height_;
    AVLNode *parent_, *left_, *right_;
};

template<typename KT, typename VT = bool>
class AVLTree
{
public:
    using Node = AVLNode<KT, VT>;

    struct Visit;

    AVLTree() : root_(nullptr)
    {
    }

    AVLTree(const AVLTree &rhs) : root_(nullptr)
    {
        root_ = deepCopy(rhs.root_);
    }

    AVLTree &operator=(const AVLTree &rhs)
    {
        if (this != &rhs)
        {
            root_ = deepCopy(rhs.root_);
        }
        return *this;
    }

    AVLTree(AVLTree &&rhs) noexcept: root_(rhs.root_)
    {
        rhs.root_ = nullptr;
    }

    AVLTree &operator=(AVLTree &&rhs) noexcept
    {
        if (this != &rhs)
        {
            root_ = rhs.root_;
            rhs.root_ = nullptr;
        }
        return *this;
    }

    ~AVLTree() noexcept
    {
        destroy(root_);
    }

    Node *search(const KT &key) const noexcept
    {
        return search(root_, key);
    }

    int size() const noexcept
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

    bool empty() const noexcept
    {
        return root_ == nullptr;
    }

    int height() const noexcept
    {
        return root_->height_;
    }

    Node *max() const noexcept
    {
        auto p = root_;
        while (p->right_) p = p->right_;
        return p;
    }

    Node *min() const noexcept
    {
        auto p = root_;
        while (p->left_) p = p->left_;
        return p;
    }

    /*
     * traversal algorithm.
     */
    template<typename F = Visit>
    void preOrderTraversal(F visit = F());

    template<typename F = Visit>
    void inOrderTraversal(F visit = F());

    template<typename F = Visit>
    void postOrderTraversal(F visit = F());

    template<typename F = Visit>
    void levelOrderTraversal(F visit = F());

    bool insert(const KT &key, const VT &val = VT());

    void deleteOf(const KT &key);

    struct Visit
    {
        std::ostream &operator()(Node *p, std::ostream &os = cout) const
        {
            if (typeid(VT) == typeid(bool))
            {
                cout << p->data_.key_ << " ";
            }
            else
            {
                cout << p->data_.key_ << "-" << p->data_.value_ << " ";
            }
            return os;
        }
    };

protected:
    void destroy(Node *root) noexcept
    {
        if (root)
        {

            destroy(root->left_);
            destroy(root->right_);

            delete root;
        }
    }

    int getHeight(AVLNode<KT, VT> *p)
    {
        if (p == nullptr) return 0;
        return p->height_;
    }

    void updateHeight(AVLNode<KT, VT> *p)
    {
        if (p == nullptr) return;
        p->height_ = std::max(getHeight(p->left_), getHeight(p->right_)) + 1;
    }

    int getBalanceFactor(AVLNode<KT, VT> *p)
    {
        return getHeight(p->left_) - getHeight(p->right_);
    }

    AVLNode<KT, VT> *deepCopy(AVLNode<KT, VT> *p);

    AVLNode<KT, VT> *search(AVLNode<KT, VT> *p, const KT &key) const noexcept;

    AVLNode<KT, VT> *leftRotation(AVLNode<KT, VT> *x);

    AVLNode<KT, VT> *rightRotation(AVLNode<KT, VT> *x);

    void fixAfterInsertion(AVLNode<KT, VT> *parent);

private:
    Node *root_;

};

template<typename KT, typename VT>
template<typename F>
void AVLTree<KT, VT>::preOrderTraversal(F visit)
{
    auto p = root_;
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

template<typename KT, typename VT>
template<typename F>
void AVLTree<KT, VT>::inOrderTraversal(F visit)
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

template<typename KT, typename VT>
template<typename F>
void AVLTree<KT, VT>::postOrderTraversal(F visit)
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

template<typename KT, typename VT>
template<typename F>
void AVLTree<KT, VT>::levelOrderTraversal(F visit)
{
    Node *p = root_, *q = nullptr;
    if (p == nullptr) return;
    auto flagLevel = new AVLNode<KT, VT>(KT());
    linear::Queue<Node *> Q;
    Q.enqueue(p);
    Q.enqueue(flagLevel);

    while (!Q.empty())
    {
        p = Q.dequeue();
        q = Q.front();
        visit(p);
        if (q == flagLevel)
        {
            Q.dequeue();
            cout << '\n';
            if (p->left_) Q.enqueue(p->left_);
            if (p->right_) Q.enqueue(p->right_);

            if (!Q.empty())
            {
                Q.enqueue(flagLevel);
            }
        }
        else
        {

            if (p->left_) Q.enqueue(p->left_);
            if (p->right_) Q.enqueue(p->right_);
        }
    }
}

template<typename KT, typename VT>
AVLNode<KT, VT> *AVLTree<KT, VT>::deepCopy(AVLNode<KT, VT> *p)
{
    if (p == nullptr) return nullptr;

    auto pLeft = deepCopy(p->left_);
    auto pRight = deepCopy(p->right_);

    auto root = new AVLNode<KT, VT>(p->data_.key_, p->data_.value_);

    root->left_ = pLeft;
    root->right_ = pRight;

    if (pLeft) pLeft->parent_ = root;
    if (pRight) pRight->parent_ = root;

    root->height_ = p->height_;

    return root;
}

template<typename KT, typename VT>
AVLNode<KT, VT> *AVLTree<KT, VT>::search(AVLNode<KT, VT> *p, const KT &key) const noexcept
{
    if (p == nullptr) return nullptr;
    while (p && key != p->data_.key_)
    {
        if (key < p->data_.key_)
        {
            p = p->left_;
        }
        else
        {
            p = p->right_;
        }
    }
    return p;
}

template<typename KT, typename VT>
AVLNode<KT, VT> *AVLTree<KT, VT>::leftRotation(AVLNode<KT, VT> *x)
{
    auto y = x->right_;
    if (x->parent_)
    {
        /* set x.parent */
        if (x->parent_->left_ == x)
        {
            x->parent_->left_ = y;
        }
        else
        {
            x->parent_->right_ = y;
        }
        y->parent_ = x->parent_;


        /* set x */
        x->right_ = y->left_;
        y->left_ ? y->left_->parent_ = x : x;

        /* set y */
        y->left_ = x;
        x->parent_ = y;

    }

    else
    {
        y->parent_ = nullptr;
        root_ = y;

        x->right_ = y->left_;
        y->left_ ? y->left_->parent_ = x : x;

        y->left_ = x;
        x->parent_ = y;

    }

    updateHeight(x);
    updateHeight(y);

    return y;

}

template<typename KT, typename VT>
AVLNode<KT, VT> *AVLTree<KT, VT>::rightRotation(AVLNode<KT, VT> *x)
{
    auto y = x->left_;
    if (x->parent_)
    {
        /* set x.parent */
        if (x->parent_->left_ == x)
        {
            x->parent_->left_ = y;
        }
        else
        {
            x->parent_->right_ = y;
        }
        y->parent_ = x->parent_;


        /* set x */
        x->left_ = y->right_;
        y->right_ ? y->right_->parent_ = x : x;


        /* set y */
        y->right_ = x;
        x->parent_ = y;
    }

    else
    {
        y->parent_ = nullptr;
        root_ = y;
        /* set x */
        x->left_ = y->right_;
        y->right_ ? y->right_->parent_ = x : x;

        /* set y*/
        y->right_ = x;
        x->parent_ = y;

    }

    updateHeight(x);
    updateHeight(y);
    return y;

}

template<typename KT, typename VT>
void AVLTree<KT, VT>::fixAfterInsertion(AVLNode<KT, VT> *parent)
{
    while (parent)
    {
        int leftHeight = getHeight(parent->left_);
        int rightHeight = getHeight(parent->right_);

        if (std::abs(getBalanceFactor(parent)) == 2)
        {

            if (leftHeight > rightHeight)
            {
                /* is LL */
                if (getBalanceFactor(parent->left_) == 1)
                {
                    rightRotation(parent);
                }
                    /* is LR*/
                else if (getBalanceFactor(parent->left_) == -1)
                {
                    leftRotation(parent->left_);
                    rightRotation(parent);
                }

            }
            else
            {
                /* is RR */
                if (getBalanceFactor(parent->right_) == -1)
                {
                    leftRotation(parent);
                }
                    /* is RL */
                else if (getBalanceFactor(parent->right_) == 1)
                {
                    rightRotation(parent->right_);
                    leftRotation(parent);
                }
            }
            break;
        }

        int newHeight = std::max(leftHeight, rightHeight) + 1;
        if (parent->height_ == newHeight)
        {
            break;
        }
        else
        {
            updateHeight(parent);
        }
        parent = parent->parent_;
    }

}

template<typename KT, typename VT>
bool AVLTree<KT, VT>::insert(const KT &key, const VT &val)
{
    if (root_ == nullptr)
    {
        root_ = new AVLNode<KT, VT>(key);
        return true;
    }
    AVLNode<KT, VT> *p = root_, *parent = nullptr;
    int cmp = 0;
    while (p)
    {
        parent = p;
        if (key < p->data_.key_)
        {
            p = p->left_;
            cmp = -1;
        }
        else if (p->data_.key_ < key)
        {
            p = p->right_;
            cmp = 1;
        }
        else
        {
            break;
        }
    }

    if (cmp == 0) return false;

    if (cmp == 1)
    {
        parent->right_ = new AVLNode<KT, VT>(key, val, parent);
    }

    if (cmp == -1)
    {
        parent->left_ = new AVLNode<KT, VT>(key, val, parent);
    }

    fixAfterInsertion(parent);
    return true;
}

}

#endif //TSINGHUA_DATASTRUCTURE_AVLTREE_H
