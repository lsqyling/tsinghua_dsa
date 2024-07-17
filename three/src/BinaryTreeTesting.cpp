//
// Created by shiqing on 19-7-13.
//

#include "../../common/CommonHeaders.h"
#include "../include/BinaryTree.h"

namespace tree {

void testingBinaryTreeNode()
{
    BinaryTreeNode<int> bi;
    BinaryTreeNode<int> b2(42);

    cout << &bi << &b2 << endl;

}

void testingBinaryTree()
{
    string pre[6]{"A", "B", "D", "E", "C", "F"};
    string in[6]{"D", "B", "E", "A", "C", "F"};

    BinaryTree<string> bTree(pre, in);

    BinaryTree<string> b1(bTree);

    cout << b1.empty() << endl;
    cout << b1.size() << endl;
    cout << b1.height() << endl;

    b1.preOrderTraversal();
    cout << endl;
    b1.inOrderTraversal();
    cout << endl;
    b1.levelOrderTraversal();

    auto b2 = b1;
    cout << b2.empty() << endl;
    cout << b2.size() << endl;
    cout << b2.height() << endl;

    b2.preOrderTraversal();
    cout << endl;
    b2.inOrderTraversal();
    cout << endl;
    b2.levelOrderTraversal();

    BinaryTree<string> b3(std::move(b2));
    cout << b3.empty() << endl;
    cout << b3.size() << endl;
    cout << b3.height() << endl;

    b3.preOrderTraversal();
    cout << endl;
    b3.inOrderTraversal();
    cout << endl;
    b3.levelOrderTraversal();

    BinaryTree<string> b4;

    b4 = std::move(b3);

    cout << b4.empty() << endl;
    cout << b4.size() << endl;
    cout << b4.height() << endl;

    b4.preOrderTraversal();
    cout << endl;
    b4.inOrderTraversal();
    cout << endl;
    b4.levelOrderTraversal();

}

}

int main(int argc, char *argv[])
{
    tree::testingBinaryTreeNode();
    tree::testingBinaryTree();

    return 0;
}