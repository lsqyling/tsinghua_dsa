//
// Created by shiqing on 19-7-22.
//
#include <cstring>
#include "../../common/CommonHeaders.h"
#include "../include/BinaryTree.h"
#include "../../part_1_linear/include/Stack.h"
#include "../../part_1_linear/include/Queue.h"
#include "../include/BinarySearchTree.h"
#include <map>

/*
 * Threaded binary Tree.
 */
template<typename T>
struct ThreadedBinNode
{
    template<typename... Args>
    explicit ThreadedBinNode(Args &&...args)
            : data_(std::forward<Args>(args)...), left_(nullptr), right_(nullptr), ltag_(0), rtag_(0)
    {
    }

    T data_;
    ThreadedBinNode *left_, *right_;
    int ltag_, rtag_;
};

namespace tree {

template<typename T> using BinNode = tree::BinaryTreeNode<T>;

/*
 * factory method.
 */
BinNode<string> *binaryTreeFactory()
{
    BinNode<string> *n1 = new BinNode<string>("A"),
            *n2 = new BinNode<string>("B"),
            *n3 = new BinNode<string>("C"),
            *n4 = new BinNode<string>("D"),
            *n5 = new BinNode<string>("E"),
            *n6 = new BinNode<string>("F"),
            *n7 = new BinNode<string>("G"),
            *n8 = new BinNode<string>("H"),
            *n9 = new BinNode<string>("I");
    n1->left_ = n2, n1->right_ = n3;
    n2->left_ = n4, n2->right_ = n5;
    n3->left_ = n6, n3->right_ = n7;
    n5->left_ = n8, n6->right_ = n9;
    return n1;
}

BinNode<string> *completeBinaryTreeFactory()
{
    BinNode<string> *n1 = new BinNode<string>("A"),
            *n2 = new BinNode<string>("B"),
            *n3 = new BinNode<string>("C"),
            *n4 = new BinNode<string>("D"),
            *n5 = new BinNode<string>("E"),
            *n6 = new BinNode<string>("F"),
            *n7 = new BinNode<string>("G"),
            *n8 = new BinNode<string>("H"),
            *n9 = new BinNode<string>("I");
    n1->left_ = n2, n1->right_ = n3;
    n2->left_ = n4, n2->right_ = n5;
    n3->left_ = n6, n3->right_ = n7;
    n4->left_ = n8, n4->right_ = n9;
    return n1;
}

template<typename T>
void destroy(T *p)
{
    if (p)
    {
        destroy(p->left_);
        destroy(p->right_);
        delete p;
    }
}

/*
 * Page 113. Question 5: closest to common parent node.
 */
int findCommonParentNode(int binTree[], int i, int j, int n)
{
    int common = 0;
    int *indexArray = new int[n + 2];
    for (int k = 1; k <= n; ++k)
    {
        indexArray[binTree[k]] = k;
    }

    int *aux = new int[n + 2]{};
    int indexI = indexArray[i];
    while (indexI /= 2)
    {
        ++aux[indexI];
    }

    int indexJ = indexArray[j];
    while (indexJ /= 2)
    {
        if (aux[indexJ])
        {
            common = binTree[indexJ];
            break;
        }
    }
    return common;
}

void testingFindCommonParentNode()
{
    int binTree[8] = {0, 1, 2, 3, 4, 0, 0, 5};
    cout << findCommonParentNode(binTree, 2, 3, 7) << endl;
}

/*
 * 后续遍历是先访问左，在访问右， 最后访问根
 * 当且仅当右子树为空或者右子树被访问过后，才会访问根节点，因此使用辅助指针r来记录最近访问的节点
 */
template<typename T>
void postOrderTraversal(BinNode<T> *BT)
{
    BinNode<T> *p = BT, *r = nullptr;
    linear::Stack<BinNode<T> *> S;
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
                p = S.pop();
                cout << p->val_ << " ";
                r = p, p = nullptr; // if p isn't given nullptr, that will case endless loop; note:
            }
        }
    }
}

/*
 * In Order Traversal version 2.0:
 * pre order: root -> left -> right ========> root, right -> left =======>reverse: left -> root -> right
 */
template<typename T>
void postOrderTraversalVerson2(BinNode<T> *BT)
{
    BinNode<T> *p = BT;
    linear::Stack<BinNode<T> *> S;
    linear::Stack<BinNode<T> *> resultS;
    while (p || !S.empty())
    {
        while (p)
        {
            S.push(p);
            resultS.push(p);
            p = p->right_;
        }
        if (!S.empty())
        {
            p = S.pop();
            p = p->left_;
        }
    }

    while (!resultS.empty())
    {
        p = resultS.pop();
        cout << p->val_ << " ";
    }

}

/*
 * preorder: root -> left -> right
 */
template<typename T>
void preorderTraversal(BinNode<T> *BT)
{
    BinNode<T> *p = BT;
    linear::Stack<BinNode<T> *> S;
    while (p || !S.empty())
    {
        while (p)
        {
            S.push(p);
            cout << p->val_ << " ";
            p = p->left_;
        }

        if (!S.empty())
        {
            p = S.pop();
            p = p->right_;
        }

    }
}

/*
 * inorder: left -> root -> right
 */
template<typename T>
void inorderTraversal(BinNode<T> *BT)
{
    BinNode<T> *p = BT;
    linear::Stack<BinNode<T> *> S;
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
            cout << p->val_ << " ";
            p = p->right_;
        }
    }
}

/*
 * level traversal
 */
template<typename T>
void levelTraversal(BinNode<T> *BT)
{
    BinNode<T> *p = BT;
    if (p == nullptr) return;
    linear::Queue<BinNode<T> *> Q;
    Q.enqueue(p);
    while (!Q.empty())
    {
        p = Q.dequeue();
        cout << p->val_ << " ";
        if (p->left_) Q.enqueue(p->left_);
        if (p->right_) Q.enqueue(p->right_);
    }
}

void testingTraversal()
{
    auto p = binaryTreeFactory();
    levelTraversal(p);
    cout << endl;
    preorderTraversal(p);
    cout << endl;
    inorderTraversal(p);
    cout << endl;
    postOrderTraversal(p);
    cout << endl;
    postOrderTraversalVerson2(p);
    destroy(p);
}

ThreadedBinNode<string> *createBinaryTreeByThreadBinNode()
{
    auto n1 = new ThreadedBinNode<string>("A"),
            n2 = new ThreadedBinNode<string>("B"),
            n3 = new ThreadedBinNode<string>("C"),
            n4 = new ThreadedBinNode<string>("D"),
            n5 = new ThreadedBinNode<string>("E"),
            n6 = new ThreadedBinNode<string>("F"),
            n7 = new ThreadedBinNode<string>("G"),
            n8 = new ThreadedBinNode<string>("H"),
            n9 = new ThreadedBinNode<string>("I");
    n1->left_ = n2, n1->right_ = n3;
    n2->left_ = n4, n2->right_ = n5;
    n3->left_ = n6, n3->right_ = n7;
    n5->left_ = n8, n6->right_ = n9;
    return n1;
}

template<typename T>
void inOrderThreadedTree(ThreadedBinNode<T> *p, ThreadedBinNode<T> *&pre)
{
    if (p)
    {
        inOrderThreadedTree(p->left_, pre);
        if (!p->left_)
        {
            p->left_ = pre;
            p->ltag_ = 1;
        }
        if (pre && pre->right_ == nullptr)
        {
            pre->right_ = p;
            pre->rtag_ = 1;
        }
        pre = p;
        inOrderThreadedTree(p->right_, pre);
    }
}

template<typename T>
void createThreadedTree(ThreadedBinNode<T> *TBT)
{
    if (TBT)
    {
        ThreadedBinNode<T> *pre = nullptr;
        inOrderThreadedTree(TBT, pre);
        pre->right_ = nullptr;
        pre->rtag_ = 1;
    }
}

template<typename T>
inline ThreadedBinNode<T> *firstNode(ThreadedBinNode<T> *p)
{
    while (p->ltag_ == 0)
    {
        p = p->left_;
    }
    return p;
}

template<typename T>
inline ThreadedBinNode<T> *nextNode(ThreadedBinNode<T> *p)
{
    if (p->rtag_ == 0) return firstNode(p->right_);
    return p->right_;
}

template<typename T>
void inOrdertraversalThreadedBinTree(ThreadedBinNode<T> *threadedBinTree)
{
    for (auto p = firstNode(threadedBinTree); p; p = nextNode(p))
    {
        cout << p->data_ << " ";
    }
}

void testingThreadedBinaryTree()
{
    auto p = createBinaryTreeByThreadBinNode();
    createThreadedTree(p);
    cout << endl;
    inOrdertraversalThreadedBinTree(p);
}
}

namespace page_126 {

template<typename T> using BinNode = tree::BinNode<T>;

/*
 * Question 3: post order traversal alg that is not recursive.
 */

template<typename T>
void postOrderTraversal(BinNode<T> *BT)
{
    BinNode<T> *p = BT, *r;
    linear::Stack<BinNode<T> *> S;
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
                p = S.pop();
                cout << p->val_ << " ";
                r = p, p = nullptr;
            }
        }
    }
}

void testingPostOrder()
{
    auto p = tree::binaryTreeFactory();
    page_126::postOrderTraversal(p);
    tree::destroy(p);
}

/*
 * Question 4: level traversal
 */
template<typename T>
void levelTraversal(BinNode<T> *BT)
{
    auto p = BT;
    if (!p) return;
    linear::Queue<BinNode<T> *> Q;
    Q.enqueue(p);
    while (!Q.empty())
    {
        p = Q.dequeue();
        cout << p->val_ << " ";
        if (p->left_) Q.enqueue(p->left_);
        if (p->right_) Q.enqueue(p->right_);
    }
}

void testingLevelTraversal()
{
    auto p = tree::binaryTreeFactory();
    page_126::levelTraversal(p);
    tree::destroy(p);
}

/*
 * Question 5: calculate the height of binary tree
 */
template<typename T>
int heightOfBinaryTree(BinNode<T> *p)
{
    if (p == nullptr) return 0;
    return std::max(heightOfBinaryTree(p->left_), heightOfBinaryTree(p->right_)) + 1;
}

template<typename T>
int heightOfBinaryTreeNoneRecursive(BinNode<T> *p)
{
    BinNode<T> *r = nullptr;
    linear::Stack<BinNode<T> *> S;
    int h = 0;
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
                if (h < S.size()) h = S.size();
                p = S.pop();
                r = p, p = nullptr;
            }
        }
    }
    return h;
}

void testingHeightOfBinaryTree()
{
    auto p = tree::binaryTreeFactory();
    cout << page_126::heightOfBinaryTree(p) << endl;
    cout << page_126::heightOfBinaryTreeNoneRecursive(p) << endl;
    tree::destroy(p);
}

/*
 * Question 6: the preorder A[1....n], inorder B[1...n], build the binary tree
 */


template<typename T, unsigned M>
BinNode<T> *construct(const T (&preorder)[M], int b, int e, const T (&inorder)[M], int lo, int hi)
{
    if (b == e || lo == hi) return nullptr;
//        construct a root of the tree
    T rootVal = preorder[b];
    auto root = new BinNode<T>(rootVal);
    root->left_ = root->right_ = nullptr;

    if (b + 1 == e && lo + 1 == hi && preorder[b] == inorder[lo])
    {
        return root;
    }

//        find the range of sub tree
    int i = lo;
    while (i < hi && inorder[i] != rootVal) i++;
    int nLeft = i - lo;
    int nRight = hi - 1 - i;

    if (nLeft)
    {
        root->left_ = construct(preorder, b + 1, b + 1 + nLeft, inorder, lo, i);
    }

    if (nRight)
    {
        root->right_ = construct(preorder, e - nRight, e, inorder, i + 1, hi);
    }

    return root;
}

template<typename T, unsigned M>
BinNode<T> *constructBinaryTree(const T (&preOrder)[M], const T (&inorder)[M])
{
    int b = 1, e = M, lo = 1, hi = M;
    return construct(preOrder, b, e, inorder, lo, hi);
}

void testingConstructBinaryTree()
{
    int A[] = {0, 1, 2, 4, 7, 3, 5, 6, 8};
    int B[] = {0, 4, 7, 2, 1, 5, 3, 8, 6};

    auto p = constructBinaryTree(A, B);

    tree::inorderTraversal(p);
    cout << endl;
    tree::preorderTraversal(p);
    tree::destroy(p);

}

/*
 * Question 7: is it a complete binary tree?
 */

template<typename T>
bool isCompleteBinaryTree(BinNode<T> *BT)
{
    auto p = BT;
    if (p == nullptr) return false;
    linear::Queue<BinNode<T> *> Q;
    Q.enqueue(p);
    while (!Q.empty())
    {
        p = Q.front();
        if (p->left_ && p->right_)
        {
            Q.dequeue();
            Q.enqueue(p->left_);
            Q.enqueue(p->right_);
        }
        else if (p->left_ == nullptr && p->right_)
        {
            return false;
        }
        else if ((p->left_ && p->right_ == nullptr) || (!p->left_ && !p->right_))
        {
            Q.dequeue();
            if (p->left_ && p->right_ == nullptr)
            {
                Q.enqueue(p->left_);
            }
            while (!Q.empty())
            {
                p = Q.dequeue();
                if (p->left_ || p->right_) return false;
            }
        }

    }
    return true;
}

void testingIsCompleteBinaryTree()
{
    auto p = tree::binaryTreeFactory();
    cout << isCompleteBinaryTree(p) << endl;
    tree::destroy(p);
    p = tree::completeBinaryTreeFactory();
    cout << isCompleteBinaryTree(p) << endl;
}

/*
 * Question 8: count branch node
 */

template<typename T>
void count2BranchNodes(BinNode<T> *p, int &cnt)
{
    if (p)
    {
        if (p->left_ && p->right_) ++cnt;
        count2BranchNodes(p->left_, cnt);
        count2BranchNodes(p->right_, cnt);
    }
}

template<typename T>
int count2BranchNodesNoRecursive(BinNode<T> *p)
{
    int cnt = 0;
    linear::Stack<BinNode<T> *> S;
    while (p || !S.empty())
    {

        while (p)
        {
            S.push(p);
            if (p->left_ && p->right_) ++cnt;
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

void testingCount2Branch()
{
    auto p = tree::binaryTreeFactory();
    cout << count2BranchNodesNoRecursive(p) << endl;
    int cnt = 0;
    count2BranchNodes(p, cnt);
    cout << cnt << endl;
}

/*
 * Question 9: swap left and right subtree
 */
template<typename T>
void swapBinaryTree(BinNode<T> *p)
{
    if (p)
    {
        swapBinaryTree(p->left_);
        swapBinaryTree(p->right_);

        std::swap(p->left_, p->right_);
    }
}

template<typename T>
void swapBinaryTreeNoneRecursive(BinNode<T> *BT)
{
    BinNode<T> *p = BT, *r = nullptr;
    linear::Stack<BinNode<T> *> S;
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
                std::swap(p->left_, p->right_);
                r = p, p = nullptr;
            }
        }
    }
}

void testingSwapBinaryTree()
{
    auto p = tree::binaryTreeFactory();
    swapBinaryTree(p);
    tree::levelTraversal(p);
    tree::destroy(p);
    p = tree::binaryTreeFactory();
    swapBinaryTreeNoneRecursive(p);
    cout << endl;
    tree::levelTraversal(p);
    tree::destroy(p);
}

/*
 * Question 10: kth of nodes's value
 */
template<typename T>
void preOrderKthValue(BinNode<T> *p, int &k, T &value)
{
    if (p)
    {
        if (--k == 0)
        {
            value = p->val_;
        }
        preOrderKthValue(p->left_, k, value);
        preOrderKthValue(p->right_, k, value);
    }
}

template<typename T>
T preOrderKthValueNoneRecursive(BinNode<T> *BT, int k)
{
    BinNode<T> *p = BT;
    linear::Stack<BinNode<T> *> S;
    while (p || !S.empty())
    {
        while (p)
        {
            S.push(p);
            if (--k == 0) return p->val_;
            p = p->left_;
        }

        if (!S.empty())
        {
            p = S.pop();
            p = p->right_;
        }
    }
    return T();
}

void testingPreOrderKthValue()
{
    auto p = tree::binaryTreeFactory();
    int k = 5;
    string s;
    preOrderKthValue(p, k, s);
    cout << s << endl;
    cout << preOrderKthValueNoneRecursive(p, 5) << endl;
}

/*
 * Question 11: delete node if node equals x;
 */

template<typename T>
BinNode<T> *findParentNode(BinNode<T> *BT, BinNode<T> *p)
{
    if (p == BT || p == nullptr) return nullptr;
    auto q = BT;
    linear::Stack<BinNode<T> *> S;
    while (q || !S.empty())
    {
        while (q)
        {
            S.push(q);
            if (q->left_ == p || q->right_ == p) return q;
            q = q->left_;
        }
        if (!S.empty())
        {
            q = S.pop();
            q = q->right_;
        }
    }
    return nullptr;
}

template<typename T>
void deleteXOfBinaryTree(BinNode<T> *p, T x)
{
    static BinNode<T> *root = p;
    if (p)
    {
        deleteXOfBinaryTree(p->left_, x);
        deleteXOfBinaryTree(p->right_, x);
        if (p->val_ == x)
        {
            auto parent = findParentNode(root, p);
            if (parent && parent->left_ == p)
            {
                parent->left_ = nullptr;
            }
            if (parent && parent->right_ == p)
            {
                parent->right_ = nullptr;
            }
            tree::destroy(p);
        }
    }
}

void testingDeleteXOfBinaryTree()
{
    auto p = tree::binaryTreeFactory();
    deleteXOfBinaryTree(p, string("B"));
    page_126::levelTraversal(p);
    cout << endl;
}

/*
 * Question 12:find the value x of nodes, and print all of their parents.
 */

constexpr int MaxSize = 256;

template<typename T>
void printParentNodes(BinNode<T> *BT, const T &x)
{
    BinNode<T> *S[MaxSize];
    int top = -1;

    BinNode<T> *p = BT, *r = nullptr;
    while (p || top != -1)
    {
        while (p)
        {
            S[++top] = p;
            p = p->left_;
        }

        if (top != -1)
        {
            p = S[top];
            if (p->right_ && p->right_ != r)
            {
                p = p->right_;
            }
            else
            {
                --top;
                if (p->val_ == x)
                {
                    for (int j = top; j > -1; --j)
                    {
                        cout << S[j]->val_ << " ";
                    }
                    cout << endl;
                }
                r = p, p = nullptr;
            }
        }
    }
}

void testingPrintParentNodes()
{
    auto p = tree::binaryTreeFactory();
    page_126::printParentNodes(p, string("E"));
    cout << endl;
}

/*
 * Question 13: find the closest parent.
 */
template<typename T>
BinNode<T> *findClosestParentNode(BinNode<T> *BT, BinNode<T> *p, BinNode<T> *q)
{
    BinNode<T> *S[MaxSize], *auxP[MaxSize], *auxQ[MaxSize];
    int top = -1, i = 0, j = 0;
    BinNode<T> *s = BT, *r = nullptr;
    while (s || top != -1)
    {
        while (s)
        {
            S[++top] = s;
            s = s->left_;
        }
        if (top != -1)
        {
            s = S[top];
            if (s->right_ && s->right_ != r)
            {
                s = s->right_;
            }
            else
            {
                --top;
                if (s == p)
                {
                    for (; i <= top; ++i)
                    {
                        auxP[i] = S[i];
                    }
                }
                if (s == q)
                {
                    for (; j <= top; ++j)
                    {
                        auxQ[j] = S[j];
                    }
                }
                r = s, s = nullptr;
            }

        }
    }

    int n = i - j;
    if (0 < n)
    {
        while (n--) --i;
    }
    if (n < 0)
    {
        n = -n;
        while (n--) --j;
    }
    while ((0 < i && 0 < j) && auxP[--i] != auxQ[--j]);

    return auxP[i];
}

void testingFindClosestParentNode()
{
    BinNode<string> *n1 = new BinNode<string>("A"),
            *n2 = new BinNode<string>("B"),
            *n3 = new BinNode<string>("C"),
            *n4 = new BinNode<string>("D"),
            *n5 = new BinNode<string>("E"),
            *n6 = new BinNode<string>("F"),
            *n7 = new BinNode<string>("G"),
            *n8 = new BinNode<string>("H"),
            *n9 = new BinNode<string>("I");
    n1->left_ = n2, n1->right_ = n3;
    n2->left_ = n4, n2->right_ = n5;
    n3->left_ = n6, n3->right_ = n7;
    n4->left_ = n8, n4->right_ = n9;

    cout << page_126::findClosestParentNode(n1, n4, n5)->val_ << endl;

}

/*
 * Question 14: find the width of a given binary tree.
 */
template<typename T>
int widthOfBinaryTree(BinNode<T> *BT)
{
    BinNode<T> *p = BT, *q = nullptr;
    if (p == nullptr) return 0;
    linear::Queue<BinNode<T> *> Q;
    auto flagLevel = new BinNode<T>;
    Q.enqueue(p);
    Q.enqueue(flagLevel);
    int maxN = 1;
    while (!Q.empty())
    {
        p = Q.dequeue();
        q = Q.front();

        if (q == flagLevel)
        {
            Q.dequeue();
            if (p->left_) Q.enqueue(p->left_);
            if (p->right_) Q.enqueue(p->right_);

            if (maxN < Q.size()) maxN = Q.size();

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
    return maxN;
}

void testingWidthOfBinaryTree()
{
    auto p = tree::binaryTreeFactory();
    cout << page_126::widthOfBinaryTree(p) << endl;
    tree::destroy(p);
}

/*
 * Question 15: list the post order of a given full binary tree, which it's pre order is known.
 */

template<typename T>
BinNode<T> *makeFullBinaryTreeByPreorder(T *preorder, int lo, int hi)
{
    if (preorder == nullptr || hi <= lo) return nullptr;
    auto root = new BinNode<T>(preorder[lo]);
    root->left_ = root->right_ = nullptr;
    if (lo + 1 == hi) return root;

    int k = (lo + hi) / 2;

    root->left_ = makeFullBinaryTreeByPreorder(preorder, lo + 1, k + 1);
    root->right_ = makeFullBinaryTreeByPreorder(preorder, k + 1, hi);

    return root;
}

template<typename T, unsigned M>
void postOrderByPreorder(T (&preorder)[M])
{
    auto p = makeFullBinaryTreeByPreorder(preorder, 0, M);
    tree::postOrderTraversal(p);
    cout << endl;
    tree::destroy(p);
}

void testingPostOrderByPreorder()
{
    int preorder[] = {1, 2, 3, 4, 5, 6, 7};
    page_126::postOrderByPreorder(preorder);
}

/*
 * Question 16: linked the leaf nodes.
 */
template<typename T>
void linkedLeafNodes(BinNode<T> *p, BinNode<T> *&lp)
{
    if (p)
    {

        if (p->left_ == nullptr && p->right_ == nullptr)
        {
            lp ? lp->right_ = p : lp;
            lp = p;
        }

        linkedLeafNodes(p->left_, lp);
        linkedLeafNodes(p->right_, lp);
    }
}

void testingLinkedLeafNodes()
{
    BinNode<string> *n1 = new BinNode<string>("A"),
            *n2 = new BinNode<string>("B"),
            *n3 = new BinNode<string>("C"),
            *n4 = new BinNode<string>("D"),
            *n5 = new BinNode<string>("E"),
            *n6 = new BinNode<string>("F"),
            *n7 = new BinNode<string>("G"),
            *n8 = new BinNode<string>("H"),
            *n9 = new BinNode<string>("I");
    n1->left_ = n2, n1->right_ = n3;
    n2->left_ = n4, n2->right_ = n5;
    n3->left_ = n6, n3->right_ = n7;
    n5->left_ = n8, n6->right_ = n9;
    BinNode<string> *pre = nullptr;
    page_126::linkedLeafNodes(n1, pre);

    auto s = n4;
    while (s)
    {
        cout << s->val_ << " ";
        s = s->right_;
    }

}

/*
 * Question 17: is similar binary tree?
 */

template<typename T>
inline bool hasOneLeaf(BinNode<T> *p)
{
    if (p == nullptr) return false;
    return (p->left_ && p->right_ == nullptr) || (p->left_ == nullptr && p->right_);
}

template<typename T>
inline bool hasTwoLeaves(BinNode<T> *p)
{
    if (p == nullptr) return false;
    return p->left_ && p->right_;
}

template<typename T>
inline bool isLeaf(BinNode<T> *p)
{
    if (p == nullptr) return false;
    return p->left_ == nullptr && p->right_ == nullptr;
}

template<typename T>
inline bool hasLeaf(BinNode<T> *p)
{
    if (p == nullptr) return false;
    return hasOneLeaf(p) || hasTwoLeaves(p);
}

template<typename T>
inline bool hasNoLeaf(BinNode<T> *p)
{
    if (p == nullptr) return true;
    return isLeaf(p);
}

template<typename T>
bool isSimilar(BinNode<T> *aT, BinNode<T> *bT)
{
    if (aT == nullptr && bT == nullptr) return true;
    if (isLeaf(aT) && isLeaf(bT)) return true;
    if (hasNoLeaf(aT) || hasNoLeaf(bT)) return false;
    if (hasOneLeaf(aT) || hasOneLeaf(bT)) return false;
    if (hasTwoLeaves(aT) || hasTwoLeaves(bT))
    {
        if (hasTwoLeaves(aT) && hasTwoLeaves(bT))
        {
            return isSimilar(aT->left_, bT->left_) && isSimilar(aT->right_, bT->right_);
        }
        return false;
    }
    return false;
}

void testingIsSimilar()
{
    BinNode<string> *n1 = new BinNode<string>("A"),
            *n2 = new BinNode<string>("B"),
            *n3 = new BinNode<string>("C"),
            *n4 = new BinNode<string>("D"),
            *n5 = new BinNode<string>("E"),
            *n6 = new BinNode<string>("F"),
            *n7 = new BinNode<string>("G"),
            *n8 = new BinNode<string>("H"),
            *n9 = new BinNode<string>("I");
    n1->left_ = n2, n1->right_ = n3;
    n2->left_ = n4, n2->right_ = n5;
    n3->left_ = n6, n3->right_ = n7;
//        n5->left_ = n8, n6->right_ = n9;

    cout << page_126::isSimilar(n2, n3) << endl;
}

/*
 * Question 18: find the succ of an given node's pre
 */
template<typename T>
inline ThreadedBinNode<T> *firstNode(ThreadedBinNode<T> *p)
{
    while (p->ltag_ == 0)
    { p = p->left_; }
    return p;
}

template<typename T>
inline ThreadedBinNode<T> *nextNode(ThreadedBinNode<T> *p)
{
    if (p->rtag_ == 0) return firstNode(p->right_);
    return p->right_;
}

template<typename T>
ThreadedBinNode<T> *preNodeInPostorder(ThreadedBinNode<T> *TBT, T val)
{
    if (TBT == nullptr) return nullptr;
    for (auto p = firstNode(TBT); p; p = nextNode(p))
    {
        if (p->data_ == val)
        {
            if (p->rtag_ == 0) return p->right_;
            if (p->ltag_ == 0) return p->left_;
            if (p->ltag_ && p->rtag_)
            {
                if (p->left_ == nullptr) return p->left_;
                else
                {
                    while (p->ltag_ && p->left_)
                    {
                        p = p->left_;
                    }
                    if (p->ltag_ == 0) return p->left_;
                    else return nullptr;
                }
            }
        }
    }
    return TBT;
}

void testingPreNodeInPostorder()
{
    ThreadedBinNode<string> *n1 = new ThreadedBinNode<string>("A"),
            *n2 = new ThreadedBinNode<string>("B"),
            *n3 = new ThreadedBinNode<string>("C"),
            *n4 = new ThreadedBinNode<string>("D"),
            *n5 = new ThreadedBinNode<string>("E"),
            *n6 = new ThreadedBinNode<string>("F"),
            *n7 = new ThreadedBinNode<string>("G"),
            *n8 = new ThreadedBinNode<string>("H"),
            *n9 = new ThreadedBinNode<string>("I");
    n1->left_ = n2, n1->right_ = n3;
    n2->left_ = n4, n2->right_ = n5;
    n3->left_ = n6, n3->right_ = n7;
    n5->left_ = n8, n6->right_ = n9;
    tree::createThreadedTree(n1);

    cout << page_126::preNodeInPostorder(n1, string("A"))->data_ << endl;
    cout << page_126::preNodeInPostorder(n1, string("B"))->data_ << endl;
    cout << page_126::preNodeInPostorder(n1, string("C"))->data_ << endl;
    cout << page_126::preNodeInPostorder(n1, string("D")) << endl;
    cout << page_126::preNodeInPostorder(n1, string("E"))->data_ << endl;
    cout << page_126::preNodeInPostorder(n1, string("F"))->data_ << endl;
    cout << page_126::preNodeInPostorder(n1, string("G"))->data_ << endl;
    cout << page_126::preNodeInPostorder(n1, string("H"))->data_ << endl;
    cout << page_126::preNodeInPostorder(n1, string("I"))->data_ << endl;

}

/*
 * Question 19: WPL
 */
struct WPLBinNode
{
    unsigned weight;
    WPLBinNode *left, *right;
};

unsigned wplBinaryTree(WPLBinNode *T)
{
    unsigned sum = 0;
    WPLBinNode *p = T;
    linear::Stack<WPLBinNode *> S;
    while (p || !S.empty())
    {

        while (p)
        {
            S.push(p);
            if (p->left == nullptr && p->right == nullptr)
            {
                sum += p->weight;
            }

            p = p->left;
        }

        if (!S.empty())
        {
            p = S.pop();
            p = p->right;
        }

    }

    return sum;
}

/*
 * Question 20: infix expression
 */
typedef struct node
{
    char data[10] = {};
    struct node *left = nullptr, *right = nullptr;
} BTree;

void printInfixExpression(BTree *p, char *s, int deep)
{
    if (p)
    {
        if (p->left == nullptr && p->right == nullptr)
        {
            std::strcat(s, p->data);
        }
        else
        {
            if (deep > 1) std::strcat(s, "(");
            printInfixExpression(p->left, s, deep + 1);
            std::strcat(s, p->data);
            printInfixExpression(p->right, s, deep + 1);
            if (deep > 1) std::strcat(s, ")");
        }
    }
}

void testingPrintInfixExpression()
{
    BTree n1, n2, n3, n4, n5, n6, n7, n8;
    n1.data[0] = '*';
    n2.data[0] = '+';
    n3.data[0] = '*';
    n4.data[0] = 'a';
    n5.data[0] = 'b';
    n6.data[0] = 'c';
    n7.data[0] = '-';
    n8.data[0] = 'd';
    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n5;
    n3.left = &n6;
    n3.right = &n7;
    n7.right = &n8;
    char str[MaxSize] = {};
    page_126::printInfixExpression(&n1, str, 1);
    std::printf("%s", str);
}

}

void TestingNamespacePage_126()
{
    page_126::testingPostOrder();
    page_126::testingLevelTraversal();
    page_126::testingHeightOfBinaryTree();
    page_126::testingConstructBinaryTree();
    page_126::testingIsCompleteBinaryTree();
    page_126::testingCount2Branch();
    page_126::testingSwapBinaryTree();
    page_126::testingPreOrderKthValue();
    page_126::testingDeleteXOfBinaryTree();
    page_126::testingPrintParentNodes();
    page_126::testingFindClosestParentNode();
    page_126::testingWidthOfBinaryTree();
    page_126::testingPostOrderByPreorder();
    page_126::testingLinkedLeafNodes();
    page_126::testingIsSimilar();
    page_126::testingPreNodeInPostorder();
    page_126::testingPrintInfixExpression();
}

void TestingNamespaceTree()
{
    tree::testingFindCommonParentNode();
    tree::testingTraversal();
    tree::testingThreadedBinaryTree();
}

namespace page_152 {

/*
 * Question 5: find out the number leaves of Tree.
 */
template<typename T>
struct CSNode
{

    template<typename... Args>
    CSNode(Args &&...params) : data_(std::forward<Args>(params)...), firstChild_(nullptr), nextSibling_(nullptr)
    {
        static_assert(
                std::is_constructible<T, Args...>::value,
                "Parameter args... can't be used to construct a T");
    }

    T data_;
    CSNode *firstChild_, *nextSibling_;
};

template<typename T>
using CSTree = CSNode<T>;

template<typename T>
int countLeaves(CSTree<T> *p)
{
    if (p == nullptr) return 0;
    if (p->firstChild_ == nullptr && p->nextSibling_ == nullptr)
    {
        return 1;
    }
    return countLeaves(p->firstChild_) + countLeaves(p->nextSibling_);
}

void testingCountLeaves()
{
    CSNode<string> n1("A"), n2("B"), n3("C"),
            n4("D"), n5("E"), n6("F"),
            n7("G");

    n1.firstChild_ = &n2;
    n2.firstChild_ = &n3;
    n2.nextSibling_ = &n4;
    n3.nextSibling_ = &n5;
    n4.nextSibling_ = &n6;
    n6.firstChild_ = &n7;

    cout << countLeaves(&n1) << endl;
}

/*
 * Question 6: find out the depth of the tree.
 */
template<typename T>
int depthOfTree(CSTree<T> *p)
{
    if (p == nullptr) return 0;
    if (p->firstChild_ == nullptr && p->nextSibling_ == nullptr) return 1;
    return std::max(depthOfTree(p->firstChild_), depthOfTree(p->nextSibling_)) + 1;
}

void testingDepthOfTree()
{
    CSNode<string> n1("A"), n2("B"), n3("C"),
            n4("D"), n5("E"), n6("F"),
            n7("G");

    n1.firstChild_ = &n2;
    n2.firstChild_ = &n3;
    n2.nextSibling_ = &n4;
    n3.nextSibling_ = &n5;
    n4.nextSibling_ = &n6;
    n6.firstChild_ = &n7;

    cout << depthOfTree(&n1) << endl;
}

/*
 * Question 7: Knowing the hierarchical sequence of a tree and the degree of each node,
 * please write an algorithm to construct the child-brother list of this tree.
 */

template<typename T>
struct NodeInfo
{
    T val_;
    int degree;
};

template<typename T>
CSTree<T> *constructOfTreeByHierarchicalOrder(NodeInfo<T> *array, int n)
{
    if (array == nullptr || n < 1) return nullptr;

    CSNode<T> **pArray = new CSNode<T> *[n];
    for (int k = 0; k < n; ++k)
    {
        pArray[k] = new CSNode<T>(array[k].val_);
    }

    int i = 0, j = i + 1;
    CSTree<T> *root = pArray[i], *p;

    while (j < n)
    {
        p = pArray[i++];
        int m = array[i].degree;
        p->firstChild_ = pArray[j++];
        p = p->firstChild_;
        --m;
        while (0 < m--)
        {
            p->nextSibling_ = pArray[j++];
            p = p->nextSibling_;
        }
    }

    delete[] pArray;

    return root;

}

template<typename T>
void preOrderTraversal(CSTree<T> *p)
{
    if (p)
    {
        cout << p->data_ << " ";
        preOrderTraversal(p->firstChild_);
        preOrderTraversal(p->nextSibling_);
    }
}

void testingConstructOfTreeByHierarchicalOrder()
{
    NodeInfo<string> array[12]{
            {"A", 3},
            {"B", 3},
            {"C", 2},
            {"D", 2},
            {"E", 1},
            {"F", 0},
            {"G", 0},
            {"H", 0},
            {"I", 0},
            {"J", 0},
            {"K", 0},
            {"L", 0}
    };

    auto p = constructOfTreeByHierarchicalOrder(array, 12);

    page_152::preOrderTraversal(p);

}
}

void TestingNamespacePage_152()
{
    page_152::testingCountLeaves();
    page_152::testingDepthOfTree();
    page_152::testingConstructOfTreeByHierarchicalOrder();
}

namespace tree_and_apply {

template<typename T>
using BSTNode = tree::BinNode<T>;

/*
 * BST : search
 */
template<typename T>
BSTNode<T> *bstSearch(BSTNode<T> *p, const T &val, BSTNode<T> *&parent)
{
    parent = nullptr;
    while (p && val != p->val_)
    {
        parent = p;
        if (val < p->val_) p = p->left_;
        else p = p->right_;
    }
    return p;
}

/*
 * BST: insert
 */
template<typename T>
int bstInsert(BSTNode<T> *&p, const T &val)
{
    if (p == nullptr)
    {
        p = new BSTNode<T>(val);
        return 1;
    }
    else if (val == p->val_)
    {
        return 0;
    }
    else if (val < p->val_)
    {
        return bstInsert(p->left_, val);
    }
    else
    {
        return bstInsert(p->right_, val);
    }
}

}

namespace page_169 {

template<typename T>
bool allNodesLessOf(tree::BinaryTreeNode<T> *root, const T &val)
{
    linear::Stack<tree::BinaryTreeNode<T> *> S;
    while (root || !S.empty())
    {
        while (root)
        {
            S.push(root);
            if (val < root->val_) return false;
            root = root->left_;
        }

        if (!S.empty())
        {
            root = S.pop();
            root = root->right_;
        }

    }
    return true;
}

template<typename T>
bool allNodesGreaterOf(tree::BinaryTreeNode<T> *root, const T &val)
{
    linear::Stack<tree::BinaryTreeNode<T> *> S;
    while (root || !S.empty())
    {
        while (root)
        {
            S.push(root);
            if (root->val_ < val) return false;
            root = root->left_;
        }

        if (!S.empty())
        {
            root = S.pop();
            root = root->right_;
        }

    }
    return true;
}

/*
 * Question 6: is it a bst_tree ?
 */
template<typename T>
bool isBSTTree(tree::BinaryTreeNode<T> *root)
{
    if (root == nullptr) return true;

    bool condi1 = true, condi2 = true;
    if (root->left_)
    {
        condi1 = allNodesLessOf(root->left_, root->val_);
    }

    if (root->right_)
    {
        condi2 = allNodesGreaterOf(root->right_, root->val_);
    }
    return condi1 && condi2 && isBSTTree(root->left_) && isBSTTree(root->right_);
}

void testingIsBSTTree()
{
    using tree::BinaryTreeNode;
    BinaryTreeNode<int> n1(6), n2(2), n3(8), n4(1), n5(4), n6(3), n7(0);
    n1.left_ = &n2;
    n1.right_ = &n3;
    n2.left_ = &n4;
    n2.right_ = &n5;
    n5.left_ = &n6;
    n5.right_ = &n7;

    BinaryTreeNode<int> *empty = nullptr;

    cout << isBSTTree(&n1) << endl;
    cout << isBSTTree(empty) << endl;
}

/*
 * Question 7: which is the layer of the given node ?
 */
template<typename T>
int layerOf(tree::BinaryTreeNode<T> *root, const T &val)
{
    int cnt = 1;
    while (root && val != root->val_)
    {
        if (val < root->val_)
        {
            root = root->left_;
            ++cnt;
        }
        else
        {
            root = root->right_;
            ++cnt;
        }
    }
    if (root) return cnt;

    return 0;
}

void testingLayerOf()
{
    tree::BinaryTreeNode<int> n1(50), n2(38), n3(70), n4(30), n5(45),
            n6(60), n7(75), n8(40), n9(48), n10(80), n11(41);

    n1.left_ = &n2;
    n1.right_ = &n3;
    n2.left_ = &n4;
    n2.right_ = &n5;
    n3.left_ = &n6;
    n3.right_ = &n7;
    n5.left_ = &n8;
    n5.right_ = &n9;
    n7.right_ = &n10;
    n8.right_ = &n11;

    cout << layerOf(&n1, 40);
    cout << layerOf(&n1, 80);
    cout << layerOf(&n1, 60);
    cout << layerOf(&n1, 20) << " ";
    cout << isBSTTree(&n1) << endl;
}

/*
 * Question 8: is it a balanced tree ?
 */

template<typename T>
int heightOf(tree::BinaryTreeNode<T> *root)
{
    if (root == nullptr) return 0;
    return std::max(heightOf(root->left_), heightOf(root->right_)) + 1;
}

template<typename T>
bool isAVLTree(tree::BinaryTreeNode<T> *root)
{
    if (root == nullptr) return true;
    int leftHeight = heightOf(root->left_);
    int rightHeight = heightOf(root->right_);

    bool b = std::abs(leftHeight - rightHeight) <= 1;

    return b && isAVLTree(root->left_) && isAVLTree(root->right_);
}

void testingIsAVLTree()
{
    tree::BinaryTreeNode<int> n1(50), n2(38), n3(70), n4(30), n5(45),
            n6(60), n7(75), n8(40), n9(48), n10(80), n11(41);

    n1.left_ = &n2;
    n1.right_ = &n3;
    n2.left_ = &n4;
    n2.right_ = &n5;
    n3.left_ = &n6;
    n3.right_ = &n7;
    n5.left_ = &n8;
    n5.right_ = &n9;
    n7.right_ = &n10;
    n8.right_ = &n11;

    cout << isAVLTree(&n1) << endl;
}

/*
 * Question 9: max() min();
 */

template<typename T>
T max(tree::BinaryTreeNode<T> *root)
{
    assert(root != nullptr);
    while (root->right_)
    {
        root = root->right_;
    }
    return root->val_;
}

template<typename T>
T min(tree::BinaryTreeNode<T> *root)
{
    assert(root != nullptr);
    while (root->left_)
    {
        root = root->left_;
    }
    return root->val_;
}

/*
 * Question 10: reverse print the value of bigger than k.
 */

template<typename T>
void reversePrintBiggerthan(tree::BinaryTreeNode<T> *root, const T &key)
{
    if (root)
    {
        reversePrintBiggerthan(root->right_, key);
        if (key <= root->val_)
        {
            cout << root->val_ << " ";
        }
        reversePrintBiggerthan(root->left_, key);
    }
}

void testingPrintBiggerthan()
{
    tree::BinaryTreeNode<int> n1(50), n2(38), n3(70), n4(30), n5(45),
            n6(60), n7(75), n8(40), n9(48), n10(80), n11(41);

    n1.left_ = &n2;
    n1.right_ = &n3;
    n2.left_ = &n4;
    n2.right_ = &n5;
    n3.left_ = &n6;
    n3.right_ = &n7;
    n5.left_ = &n8;
    n5.right_ = &n9;
    n7.right_ = &n10;
    n8.right_ = &n11;
    reversePrintBiggerthan(&n1, 50);
}

template<typename KT, typename VT>
int theLengthOfS(tree::BSTNode<KT, VT> *root, tree::BSTNode<KT, VT> *x)
{
    linear::Stack<tree::BSTNode<KT, VT> *> S;
    tree::BSTNode<KT, VT> *r = nullptr;
    while (root || !S.empty())
    {
        while (root)
        {
            S.push(root);
            root = root->left_;
        }

        if (!S.empty())
        {

            root = S.top();

            if (root->right_ && root->right_ != r)
            {
                root = root->right_;
            }
            else
            {
                S.pop();
                if (root == x)
                {
                    return S.size();
                }
                r = root, root = nullptr;
            }

        }

    }
    return 0;
}

template<typename T, unsigned M>
int constructHuffmanTree(const T (&arr)[M])
{
    using tree::BSTNode;
    tree::BinarySearchTree<T, BSTNode<T, bool> *> set;
    for (int i = 0; i < M; ++i)
    {
        set.insert(arr[i], new BSTNode<T, bool>(arr[i]));
    }

    BSTNode<T, bool> *huffmanRoot_ = nullptr;
    BSTNode<T, BSTNode<T, bool> *> *fMin = nullptr, *sMin = nullptr;
    while (!set.empty())
    {
        fMin = set.min();
        huffmanRoot_ = new BSTNode<T, bool>;
        huffmanRoot_->left_ = fMin->data_.value_;
        set.deleteOf(fMin->data_.key_);
        if (!set.empty())
        {
            sMin = set.min();
            huffmanRoot_->right_ = sMin->data_.value_;
            set.deleteOf(sMin->data_.key_);
        }
        huffmanRoot_->data_.key_ = huffmanRoot_->left_->data_.key_ + huffmanRoot_->right_->data_.key_;

        if (!set.empty())
        {
            set.insert(huffmanRoot_->data_.key_, huffmanRoot_);
        }
    }

    int wpl = 0;

    auto p = huffmanRoot_;
    linear::Stack<BSTNode<T, bool> *> S;
    while (p || !S.empty())
    {
        while (p)
        {
            S.push(p);

            if (p->left_ == nullptr && p->right_ == nullptr)
            {
                int s = theLengthOfS(huffmanRoot_, p);
                wpl += s * p->data_.key_;
            }

            p = p->left_;
        }

        if (!S.empty())
        {
            p = S.pop();
            p = p->right_;
        }

    }

    return wpl;

}

void testingConstructHuffmanTree()
{
    int arr[6]{45, 12, 13, 5, 9, 16};
    cout << "WPL = " << constructHuffmanTree(arr) << endl;
}

/*
 * Question 12: the Kth min of element
 */

template<typename T>
struct BSTNode
{

    BSTNode() : data_(), count_(0), lChild_(nullptr), rChild_(nullptr)
    {
    }

    explicit BSTNode(const T &val, int count = 0)
            : data_(val), count_(count), lChild_(nullptr), rChild_(nullptr)
    {
    }

    T data_;
    int count_;
    BSTNode *lChild_, *rChild_;
};

/*
 * Kth min of element  O(logn)
 */
template<typename T>
BSTNode<T> *findKthNode(BSTNode<T> *root, int k)
{
    if (k < 1 || root == nullptr || k > root->count_) return nullptr;

    if (root->lChild_ == nullptr)
    {
        if (k == 1) return root;
        else return findKthNode(root->rChild_, k - 1);

    }

    else
    {

        if (root->lChild_->count_ == k - 1)
        {
            return root;
        }
        else if (root->lChild_->count_ > k - 1)
        {
            return findKthNode(root->lChild_, k);
        }
        else
        {
            return findKthNode(root->rChild_, k - root->lChild_->count_ - 1);
        }

    }

}

/*
 * an other way, O(n);
 */
template<typename T>
BSTNode<T> *kthNodeOf(BSTNode<T> *root, int &k)
{
    if (k < 1 || root == nullptr) return nullptr;
    BSTNode<T> *target = nullptr;

    if (root->lChild_)
    {
        target = kthNodeOf(root->lChild_, k);
    }

    if (target == nullptr)
    {
        if (k == 1)
        {
            target = root;
        }
        --k;
    }

    if (target == nullptr && root->rChild_)
    {
        target = kthNodeOf(root->rChild_, k);
    }
    return target;
}

void testingFindKthNode()
{
    BSTNode<int> n1(53, 8), n2(17, 4), n3(78, 3), n4(9, 1),
            n5(45, 2), n6(65, 1), n7(87, 1), n8(23, 1);

    n1.lChild_ = &n2;
    n1.rChild_ = &n3;
    n2.lChild_ = &n4;
    n2.rChild_ = &n5;
    n3.lChild_ = &n6;
    n3.rChild_ = &n7;
    n5.lChild_ = &n8;

    BSTNode<int> *p = nullptr;
    for (int i = 0; i < 10; ++i)
    {
        p = findKthNode(&n1, i);
        if (p)
        {
            cout << p->data_ << " ";
        }
    }
    cout << endl;

    int j;
    for (int i = 0; i < 10; ++i)
    {
        j = i;
        p = kthNodeOf(&n1, j);
        if (p)
        {
            cout << p->data_ << " ";
        }
    }
    cout << endl;
}



/*
 *
 */




















}

void TestingNamespacePage_169()
{
    page_169::testingIsBSTTree();
    page_169::testingLayerOf();
    page_169::testingIsAVLTree();
    page_169::testingPrintBiggerthan();
    page_169::testingConstructHuffmanTree();
    page_169::testingFindKthNode();
}

int main(int argc, char *argv[])
{
    TestingNamespacePage_169();
    return 0;
}