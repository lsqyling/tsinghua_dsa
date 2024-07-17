//
// Created by shiqing on 19-8-1.
//

#include "../include/BinarySearchTree.h"

namespace tree {

void testingInsert()
{

    static std::default_random_engine e;
    static std::uniform_int_distribution<int> u(0, 1000);

    BinarySearchTree<int> btree;

    for (int i = 0; i < 1000; ++i)
    {
        btree.insert(u(e));
    }

    for (int j = 0; j < 800; ++j)
    {
        btree.deleteOf(u(e));
    }

    btree.inOrderTraversal();
    cout << endl;
    btree.preOrderTraversal();

    cout << endl;
    auto b1 = btree;
    b1.preOrderTraversal();
    cout << endl;
    b1.inOrderTraversal();
    cout << endl;

    auto b2 = std::move(btree);
    b2.preOrderTraversal();
    cout << endl;
    b2.inOrderTraversal();
    cout << endl;

    cout << "btree has been removed" << endl;
    btree.inOrderTraversal();

    BinarySearchTree<int> b3, b4;

    b3 = b2;

    cout << endl;
    b3.preOrderTraversal();
    cout << endl;
    b3.inOrderTraversal();
    cout << endl;

    b4 = std::move(b3);
    b4.preOrderTraversal();
    cout << endl;
    b4.inOrderTraversal();
    cout << endl;
    cout << endl;
    cout << "-----------------------------------------------------------------------" << endl;

    BinarySearchTree<int> s1;

    for (int k = 0; k < 10; ++k)
    {
        s1.insert(k);
    }

    cout << s1.empty() << endl;

    for (int l = 0; l < 10; ++l)
    {
        s1.deleteOf(l);
    }

    cout << s1.empty() << endl;

}

}

int main(int argc, char *argv[])
{
    tree::testingInsert();

    return 0;
}