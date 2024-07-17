//
// Created by shiqing on 2020/5/25.
//
#include "tree_node.h"
#include "binary_tree.h"
#include "binary_search_tree.h"
#include "../../common/CommonHeaders.h"

namespace binary_tree_and_node {
using namespace tree;

void testingBinaryTree()
{
    char pre[] = {'A', 'B', 'D', 'F', 'E', 'C', 'G', 'H', 'I'};
    char in[] = {'D', 'B', 'E', 'F', 'A', 'G', 'H', 'C', 'I'};
    BinaryTree<char> T(pre, in);
    auto f = [](auto p)
    { cout << p->data_ << " "; };
    T.traversalIn(f);
    cout << endl;
    T.traversalLevel(f);
    T.traversalPost(f);
    cout << endl;
    T.traversalPre(f);

    cout << T.empty() << endl;
    cout << T.size() << endl;
    auto root = T.root();
    cout << "---------------" << endl;
    while (root)
    {
        cout << root->data_ << " ";
        root = root->succ();
    }
    cout << "\n---------------" << endl;


    BinaryTree<int> ti;
    ti.insertAsRoot(42);
    cout << ti.root()->data_ << endl;
    auto *x = new BinaryTreeNode<int>(0);
    ti.insertAsLC(x, 3);
    ti.insertAsRC(x, 4);
    ti.traversalLevel(f);
    cout << endl;
    x->traversalLevel(f);
    auto *p = &ti;
    ti.attachAsLC(x, p);
    x->traversalLevel(f);
}
}

namespace bst {
using namespace tree;

void testing()
{
    BST<int> t;
    int pre[] = {16, 10, 5, 2, 4, 8, 11, 15, 13, 25, 19, 17, 22, 28, 27, 37, 33};
    for (int i = 0; i < 17; ++i)
    {
        t.insert(pre[i]);
    }
    t.traversalIn([](auto *x)
                  { cout << x->data_ << " "; });
}


}


int main(int argc, char *argv[])
{
    binary_tree_and_node::testingBinaryTree();
    bst::testing();

    return 0;


}


