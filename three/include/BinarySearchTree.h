//
// Created by shiqing on 19-8-1.
//

#ifndef TSINGHUA_DATASTRUCTURE_BINARYSEARCHTREE_H
#define TSINGHUA_DATASTRUCTURE_BINARYSEARCHTREE_H

#include "../../common/CommonHeaders.h"
#include "../../part_1_linear/include/Stack.h"
#include "../../part_1_linear/include/Queue.h"

namespace tree {

template<typename K, typename V>
struct BSTNode
{

    BSTNode()
            : data_(),
              parent_(nullptr), left_(nullptr), right_(nullptr)
    {
    }

    BSTNode(const K &key, BSTNode *parent) : data_(key), parent_(parent), left_(nullptr), right_(nullptr)
    {
    }

    explicit BSTNode(const K &key, const V &val = V())
            : data_(key, val),
              parent_(nullptr), left_(nullptr), right_(nullptr)
    {

    }

    struct Pair
    {
        explicit Pair(const K &key = K(), const V &val = V()) : key_(key), value_(val)
        {
        }

        K key_;
        V value_;
    };

    Pair data_;

    BSTNode *parent_, *left_, *right_;
};

template<typename KT, typename VT = bool>
class BinarySearchTree
{
public:
    using Node = BSTNode<KT, VT>;

    BinarySearchTree() : root_(nullptr)
    {
    }

    BinarySearchTree(const BinarySearchTree &rhs);

    BinarySearchTree &operator=(const BinarySearchTree &rhs);

    BinarySearchTree(BinarySearchTree &&rhs) noexcept;

    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept;

    bool empty() const noexcept
    {
        return root_ == nullptr;
    }

    ~BinarySearchTree() noexcept
    {
        destroy(root_);
    }

    void preOrderTraversal() const noexcept
    {
        auto p = root_;
        linear::Stack<Node *> S;
        while (p || !S.empty())
        {

            while (p)
            {
                S.push(p);
                cout << p->data_.key_ << " ";
                p = p->left_;
            }

            if (!S.empty())
            {
                p = S.pop();
                p = p->right_;
            }
        }
    }

    void inOrderTraversal() const noexcept
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
                cout << p->data_.key_ << " ";
                p = p->right_;
            }
        }
    }

    Node *min() const noexcept;

    Node *max() const noexcept;

    Node *search(const KT &key) const noexcept;

    bool insert(const KT &key, const VT &val = VT());

    void deleteOf(const KT &key);

private:
    void destroy(Node *p) noexcept
    {
        if (p)
        {

            destroy(p->left_);
            destroy(p->right_);

            delete p;

        }
    }

private:
    Node *root_;
};

namespace Helper {

template<typename KT, typename VT>
auto min(BSTNode<KT, VT> *p)
{
    while (p && p->left_)
    {
        p = p->left_;
    }
    return p;
}

template<typename KT, typename VT>
auto max(BSTNode<KT, VT> *p)
{
    while (p && p->right_)
    {
        p = p->right_;
    }
    return p;
}

template<typename KT, typename VT>
BSTNode<KT, VT> *search(BSTNode<KT, VT> *p, const KT &key) noexcept
{
    while (p && key != p->data_.key_)
    {
        if (key < p->data_.key_) p = p->left_;
        else p = p->right_;
    }
    return p;
}

template<typename KT, typename VT>
bool insert(BSTNode<KT, VT> *&root, const KT &key, const VT &val)
{
    if (root == nullptr)
    {
        root = new BSTNode<KT, VT>(key, val);
        return true;
    }
    auto p = root;
    if (key < p->data_.key_)
    {

        if (p->left_ == nullptr)
        {
            auto pNode = new BSTNode<KT, VT>(key, val);
            p->left_ = pNode;
            pNode->parent_ = p;
            return true;
        }
        else
        {
            return insert(p->left_, key, val);
        }
    }
    else if (p->data_.key_ < key)
    {

        if (p->right_ == nullptr)
        {
            auto pNode = new BSTNode<KT, VT>(key, val);
            p->right_ = pNode;
            pNode->parent_ = p;
            return true;
        }
        else
        {

            return insert(p->right_, key, val);
        }

    }
    else
    {
        return false;
    }

}

template<typename KT, typename VT>
void deleteOf(BSTNode<KT, VT> *&root, const KT &x)
{
    auto px = search(root, x);
    if (px == nullptr) return;
    /*
     * check if we are deleting the root node
     */
    if (px == root)
    {
        /*
         * if deleting the root node
         * case 1: x is a leaf.
         */
        if (px->left_ == nullptr && px->right_ == nullptr)
        {
            root = nullptr;
        }
            /*
             * case 2: x has one child.
             * case 2.1: x has left child, no right child.
             */
        else if (px->right_ == nullptr)
        {
            px->left_->parent_ = nullptr;
            root = px->left_;
        }
            /*
             * case 2.2: x has right child, no left child.
             */
        else if (px->left_ == nullptr)
        {
            px->right_->parent_ = nullptr;
            root = px->right_;
        }
            /*
             * case 3: x have two child.
             */
        else
        {

            auto py = px->right_;
            while (py->left_)
            {
                py = py->left_;
            }

            /*
             * special case : py == px.right_
             */
            if (py == px->right_)
            {
                py->left_ = px->left_;
                py->parent_ = nullptr;
                root = py;
            }
                /*
                 * general case : py != px.right_
                 */
            else
            {

                auto pyParent = py->parent_;
                auto pyRight = py->right_;

                py->parent_ = nullptr;
                root = py;

                py->left_ = px->left_;
                py->right_ = px->right_;
                px->left_->parent_ = py;
                px->right_->parent_ = py;

                pyParent->left_ = pyRight;

                if (pyRight)
                {
                    pyRight->parent_ = pyParent;
                }
            }
        }
    }

        /*
         * if not deleting the root node
         */
    else
    {
        /*
         * case 1: x is a leaf.
         */
        if (px->left_ == nullptr && px->right_ == nullptr)
        {

            /*
             * update parent's child pointers
             */
            if (px->parent_->left_ == px)
            {
                px->parent_->left_ = nullptr;
            }

            else
            {
                px->parent_->right_ = nullptr;
            }

        }
            /*
             * case 2: x has one child.
             * case 2.1: x has left child, no right child.
             */
        else if (px->right_ == nullptr)
        {

            if (px->parent_->right_ == px)
            {
                px->parent_->right_ = px->left_;
            }
            else
            {
                px->parent_->left_ = px->left_;
            }
            px->left_->parent_ = px->parent_;

        }
            /*
             * case 2.2: x has right child, no left child.
             */
        else if (px->left_ == nullptr)
        {

            if (px->parent_->right_ == px)
            {
                px->parent_->right_ = px->right_;
            }
            else
            {
                px->parent_->left_ = px->right_;
            }

            px->right_->parent_ = px->parent_;

        }

            /*
             * case 3: x have two child.
             */
        else
        {

            auto py = px->right_;
            while (py->left_)
            {
                py = py->left_;
            }

            /*
             * special case : py == px.right_
             */
            if (py == px->right_)
            {

                if (px->parent_->left_ == px)
                {
                    px->parent_->left_ = py;

                }
                else
                {
                    px->parent_->right_ = py;
                }

                py->parent_ = px->parent_;
                py->left_ = px->left_;
                px->left_->parent_ = py;

            }
                /*
                 * general case : py != px.right_
                 */
            else
            {

                auto pyParent = py->parent_;
                auto pyRight = py->right_;

                if (px->parent_->left_ == px)
                {
                    px->parent_->left_ = py;

                }
                else
                {
                    px->parent_->right_ = py;
                }
                py->parent_ = px->parent_;

                py->left_ = px->left_;
                py->right_ = px->right_;
                px->left_->parent_ = py;
                px->right_->parent_ = py;

                pyParent->left_ = pyRight;

                if (pyRight)
                {
                    pyRight->parent_ = pyParent;
                }
            }
        }
    }

    delete px;

}

template<typename KT, typename VT>
BSTNode<KT, VT> *deeplyCopy(BSTNode<KT, VT> *root)
{
    if (root == nullptr) return nullptr;
    auto left = deeplyCopy(root->left_);
    auto right = deeplyCopy(root->right_);

    auto p = new BSTNode<KT, VT>(root->data_.key_, root->data_.value_);

    p->left_ = left;
    p->right_ = right;

    if (left)
    {
        left->parent_ = p;
    }
    if (right)
    {
        right->parent_ = p;
    }

    return p;
}
}

template<typename KT, typename VT>
BinarySearchTree<KT, VT>::BinarySearchTree(const BinarySearchTree &rhs)
{
    root_ = Helper::deeplyCopy(rhs.root_);
}

template<typename KT, typename VT>
BinarySearchTree<KT, VT> &BinarySearchTree<KT, VT>::operator=(const BinarySearchTree &rhs)
{
    if (this != &rhs)
    {
        root_ = Helper::deeplyCopy(rhs.root_);
    }
    return *this;
}

template<typename KT, typename VT>
BinarySearchTree<KT, VT>::BinarySearchTree(BinarySearchTree &&rhs) noexcept
{
    root_ = rhs.root_;
    rhs.root_ = nullptr;
}

template<typename KT, typename VT>
BinarySearchTree<KT, VT> &BinarySearchTree<KT, VT>::operator=(BinarySearchTree &&rhs) noexcept
{
    if (this != &rhs)
    {
        root_ = rhs.root_;
        rhs.root_ = nullptr;
    }
    return *this;
}

template<typename KT, typename VT>
typename BinarySearchTree<KT, VT>::Node *BinarySearchTree<KT, VT>::min() const noexcept
{
    return Helper::min(root_);
}

template<typename KT, typename VT>
typename BinarySearchTree<KT, VT>::Node *BinarySearchTree<KT, VT>::max() const noexcept
{
    return Helper::max(root_);
}

template<typename KT, typename VT>
typename BinarySearchTree<KT, VT>::Node *BinarySearchTree<KT, VT>::search(const KT &key) const noexcept
{
    return Helper::search(root_, key);
}

template<typename KT, typename VT>
bool BinarySearchTree<KT, VT>::insert(const KT &key, const VT &val)
{
    return Helper::insert(root_, key, val);
}

template<typename KT, typename VT>
void BinarySearchTree<KT, VT>::deleteOf(const KT &key)
{
    Helper::deleteOf(root_, key);
}

}

#endif //TSINGHUA_DATASTRUCTURE_BINARYSEARCHTREE_H
