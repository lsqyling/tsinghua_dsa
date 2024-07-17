//
// Created by shiqing on 19-8-3.
//

#include "../include/AVLTree.h"

namespace tree {

void testingAVLTree()
{

    AVLTree<int> T1;

    for (int i = 0; i < 100; ++i)
    {
        T1.insert(i);
    }

    AVLTree<int> T2(T1);

    T2.preOrderTraversal();
    cout << endl;
    T2.inOrderTraversal();
    cout << endl;
    T2.levelOrderTraversal();
    cout << endl;

    AVLTree<int> T3;

    T3 = T2;

    T3.preOrderTraversal();
    cout << endl;
    T3.inOrderTraversal();
    cout << endl;
    T3.levelOrderTraversal();
    cout << endl;

    auto p = T3.search(99);
    cout << p->data_.key_ << endl;

    cout << T3.max()->data_.key_ << endl;
    cout << T3.min()->data_.key_ << endl;
    cout << T3.empty() << endl;
    cout << T3.size() << endl;
    cout << T3.height() << endl;
    T3.postOrderTraversal();

    AVLTree<int> T5;
    for (int j = 1; j < 8; ++j)
    {
        T5.insert(j);
    }
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    T5.levelOrderTraversal();

}

}

int main(int argc, char *argv[])
{
    tree::testingAVLTree();

    return 0;
}