//
// Created by shiqing on 2020/7/6.
//

#ifndef TSINGHUA_DATASTRUCTURE_BINARY_SEARCH_TREE_H
#define TSINGHUA_DATASTRUCTURE_BINARY_SEARCH_TREE_H

namespace tree {
template<typename Key>
class BST : public BinaryTree<Key>
{
public:
    using BinaryTree<Key>::BinaryTree;

    virtual Node <Key> *&search(const Key &e);

    virtual Node <Key> *insert(const Key &e);

    virtual bool remove(const Key &e);

protected:
    Node <Key> *hot_;

    Node <Key> *connect34(Node <Key> *a, Node <Key> *b, Node <Key> &c,
                          Node <Key> *t0, Node <Key> *t1, Node <Key> *t2, Node <Key> *t3);

    Node <Key> *rotateAt(Node <Key> *x);
};

template<typename Key>
Node <Key> *&searchIn(Node <Key> *&v, const Key &e, Node <Key> *&hot)
{
    if (v == nullptr || e == v->data_) return v;
    hot = v;
    if (e < v->data_) return searchIn(v->left_, e, hot);
    else return searchIn(v->right_, e, hot);
}

template<typename Key>
Node <Key> *removeAt(Node <Key> *&x, Node <Key> *&hot)
{
    Node<Key> *w = x, *succ = nullptr;
    if (x->left_ == nullptr)
    {
        succ = x = x->right_;
    }
    else if (x->right_ == nullptr)
    {
        succ = x = x->left_;
    }
    else
    {
        w = w->succ();
        std::swap(x->data_, w->data_);
        auto u = w->parent_;
        (u == x ? u->right_ : u->left_) = succ = w->right_;
    }
    hot = w->parent_;
    if (succ) succ->parent_ = hot;
    delete w;
    return succ;
}

template<typename Key>
Node <Key> *&BST<Key>::search(const Key &e)
{
    return searchIn(this->root_, e, hot_ = nullptr);
}

template<typename Key>
Node <Key> *BST<Key>::insert(const Key &e)
{
    Node<Key> *&x = search(e);
    if (x != nullptr) return x;
    x = new Node<Key>(e, hot_);
    ++this->size_;
    this->updateHeightAbove(x);
    return x;
}


template<typename Key>
bool BST<Key>::remove(const Key &e)
{
    auto &x = search(e);
    if (x == nullptr) return false;
    removeAt(x, hot_);
    --this->size_;
    this->updateHeightAbove(hot_);
    return true;
}
}

#endif //TSINGHUA_DATASTRUCTURE_BINARY_SEARCH_TREE_H
