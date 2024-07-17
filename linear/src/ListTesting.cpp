//
// Created by shiqing on 19-5-23.
//

#include "../include/List.h"
#include "../include/Vector.h"
#include "../../common/CommonHeaders.h"

using namespace linear;

void testingConstructor()
{
    List<int> l1(10);
    cout << l1 << "l1.size = " << l1.size() << ":" << l1.empty() << endl;

    List<int> l2(9, 100);
    cout << l2 << "l2.size = " << l2.size() << ":" << l2.empty() << endl;

    List<int> l3{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << l3 << "l3.size = " << l3.size() << ":" << l3.empty() << endl;

    Vector<int> vi = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    List<int> l4(vi.begin(), vi.end());
    cout << l4 << "l4.size = " << l4.size() << ":" << l4.empty() << endl;

    List<int> l5(l4);
    cout << l5 << "l5.size = " << l5.size() << ":" << l5.empty() << endl;

    List<int> l6(std::move(l2));
    cout << l6 << "l6.size = " << l6.size() << ":" << l6.empty() << endl;

    List<int> l7;
    l7 = l5;
    cout << l7 << "l7.size = " << l7.size() << ":" << l7.empty() << endl;

    List<int> l8;
    l8 = std::move(l7);
    cout << l8 << "l8.size = " << l8.size() << ":" << l8.empty() << endl;

    List<int> l9(10L, 9);
    cout << l9 << "l9.size = " << l9.size() << ":" << l9.empty() << endl;

}

void testingListReadAndWrite()
{
    List<int> li = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    li.resize(30);
    cout << li << ": " << li.size() << ": " << li.empty() << endl;
    li.resize(10);
    cout << li << ": " << li.size() << ": " << li.empty() << endl;

    for (int i = 0; i != 9; ++i)
    {
        li.pushFront(i);
        li.pushFront(std::move(i));
    }
    cout << li << ": " << li.size() << ": " << li.empty() << endl;

    for (int j = 0; j != 18; ++j)
    {
        li.popFront();
    }
    cout << li << ": " << li.size() << ": " << li.empty() << endl;

    for (int k = 0; k != 10; ++k)
    {
        li.popBack();
    }
    cout << li << ": " << li.size() << ": " << li.empty() << endl;

    for (int l = 0; l != 10; ++l)
    {
        li.insert(li.begin(), l);
        li.insert(li.begin(), std::move(l));
    }
    cout << li << ": " << li.size() << ": " << li.empty() << endl;
    li.clear();

    std::initializer_list<int> copy{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    li.insert(li.begin(), copy);
    cout << li << ": " << li.size() << ": " << li.empty() << endl;

    for (int m = 0; m != 5; ++m)
    {
        li.erase(li.begin());
    }
    li.erase(++li.begin());
    cout << li << ": " << li.size() << ": " << li.empty() << endl;

    li.remove(9);
    cout << li << ": " << li.size() << ": " << li.empty() << endl;

    li.removeIf([](int i)
                { return i >= 7; });
    cout << li << ": " << li.size() << ": " << li.empty() << endl;

    for (int n = 0; n < 25; n += 2)
    {
        li.pushBack(n);
    }
    cout << li << ": " << li.size() << ": " << li.empty() << endl;

    cout << (li.find(17) == li.end()) << endl;
    cout << *li.search(17) << endl;
    cout << *li.selectMax() << endl;
}

void testingAlg()
{
    List<int> li{0, 3, 5, 6};
    List<int> rhs{4, 7, 11, 12, 13, 16, 17};
    li.merge(rhs);
    cout << li << endl;
    cout << *li.search(10) << endl;

    List<int> l1{9, 8, 7, 6, 5, 4, 3, 2, 2, 1, 0};
    l1.sort();
    cout << "l1: " << l1 << endl;

    List<int> l2{1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 5, 5, 5};
    long n = l2.deduplicate();
    cout << l2 << ":" << n << endl;

    List<int> l3{0, 1, 1, 1, 3, 3, 3, 3, 5, 5, 5, 5, 5, 7, 8, 9, 10};
    long oldSz = l3.size();
    long n1 = l3.uniquely();
    cout << l3 << ": " << (l3.size() == oldSz - n1) << endl;

    List<int> l4{0, 2, 3, 5};
    cout << l4.uniquely() << endl;

}

void testingReverse()
{
    List<int> li{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    li.reverse();
    cout << li << endl;
}

void testingPushAndPop()
{
    List<int> li;
    for (int i = 0; i < 5; ++i)
    {
        li.pushBack(i);
    }
    cout << li << endl;
    cout << li.size() << " " << !li.empty() << endl;
}

int main()
{
//    testingConstructor();
//    testingListReadAndWrite();
//    testingAlg();
//
//    testingReverse();
    testingPushAndPop();
    return 0;
}