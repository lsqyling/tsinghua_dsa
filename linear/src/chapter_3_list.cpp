//
// Created by shiqing on 2020/5/13.
//

#include "SList.h"
#include "../../common/CommonHeaders.h"

namespace slist_test {
using namespace linear;

void testingConstructor()
{
    SList<int> l1;
    for (int i = 0; i < 10; ++i)
    {
        l1.insertAsLast(i);
    }
    SList<int> l2(l1), l3(l2, 5, 5);
    SList<int> l4(l2.first(), 10);
    cout << l1 << endl;
    cout << l1.size() << endl;
    cout << l2 << endl;
    cout << l2.size() << endl;
    cout << l3 << endl;
    cout << l3.size() << endl;
    cout << l4 << endl;
    cout << l4.size() << endl;
    SList<int> l5(l3);
    l5 = l1;
    cout << l5 << endl;
    cout << l5.size() << endl;
}

template<typename T>
void pf(T &e)
{
    e *= 2;
}

void testingAll()
{
    SList<int> l1;
    static std::default_random_engine e(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> u(0, 0xffff);
    for (int i = 0; i < 0xffff; ++i)
    {
        l1.insertAsFirst(u(e));
    }
    cout << l1.size() << endl;
    cout << l1.empty() << endl;
    const auto &l2 = l1;
    for (int j = 0; j < 10; ++j)
    {
        cout << l2[j] << " " << l1[j] << " ";
    }
    cout << endl;
    cout << l2.first()->data_ << " " << l2.last()->data_ << endl;
    cout << l2.vaild(l2.last()) << endl;
    cout << l2.disordered() << endl;
    auto p = l2.find(12345);
    cout << (p ? p->data_ : 0) << endl;
    SList<int> l3;
    for (int k = 10; k > 0; --k)
    {
        l3.insertAsLast(k);
    }
    l3.sort();
    l1.sort();
    cout << l3 << endl;
    cout << l1.disordered() << endl;
    cout << l1.selectMax()->data_ << endl;
    SList<int> l4;
    for (int i = 0; i < 10; ++i)
    {
        l4.insertAsFirst(i);
        l4.insertPrev(l4.first(), i);
        l4.insertSucc(l4.last(), i);
    }
    cout << l4 << endl;
    l4.remove(l4.first());
    l4.remove(l4.first());
    cout << l4 << endl;
    SList<int> l5(l4);
    l4.clear();
    cout << l4.size() << endl;
    l5.sort();
    l5.merge(l3);
    cout << l5 << endl;
    SList<int> l6(l5);
    SList<int> l7(l6);
    l5.deduplicate();
    cout << l5 << endl;
    l6.uniquify();
    cout << l6 << endl;
    l6.reverse();
    cout << l6 << endl;
    cout << l7 << endl;
    l7.reverse();
    cout << l7 << endl;
    l7.uniquify();
    l7.traverse(pf);
    cout << l7 << endl;
    l7.traverse([](auto &e)
                { e /= 2; });
    cout << l7 << endl;
}


}


int main(int argc, char *argv[])
{
    slist_test::testingConstructor();
    slist_test::testingAll();

    return 0;
}