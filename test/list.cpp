#include <list>
#include <vector>
#include <format>
#include "dsa/list.hpp"

void test_list()
{
    ds::list<int> li0;
    for (int i = 0; i < 5; ++i) {
        li0.insert(li0.begin(), i);
    }
    li0.show();
    for (int i = 0; i < 5; ++i) {
        li0.insert(li0.end(), i);
    }
    li0.show();

    auto it = li0.insert(++li0.begin(), 5);
    std::cout << *--it << "\n";

    li0.show();
    li0.insert(--li0.end(), 6);
    li0.show();

    it = li0.begin();
    it++;
    li0.insert(it, 7);
    li0.show();

    it = li0.end();
    it--;
    li0.insert(it, 8);
    li0.show();

    ds::list<int> li1;
    li1.insert(li1.begin(), 3, 0);
    li1.show();

    int iarray[3]{0, 1, 2};
    ds::list<int> li2;
    li2.insert(li2.begin(), 3);
    it = li2.insert(li2.begin(), iarray, iarray + 3);
    std::cout << *it << "\n";
    li2.show();

    it = li2.erase(li2.begin());
    std::cout << *it << "\n";
    li2.show();

    ds::list<std::string> li3;
    std::vector<std::string> text{"abc", "ef", "gf", "mk", "jk"};
    li3.insert(li3.begin(), text.begin(), text.end());
    li3.show();

    auto its = li3.erase(li3.begin());
    std::cout << *its << "\n";
    li3.show();

    its = li3.erase(++li3.begin(), --li3.end());
    std::cout << *its << "\n";
    li3.show();

    li3.clear();
    li3.show();

    li3.assign(3, "abc");
    li3.show();
    li3.assign(1, "hello");
    li3.show();

    li3.resize(5, "world");
    li3.show();

    li3.resize(2, "");
    li3.show();

    ds::list<int> li4;
    li4.resize(10);
    li4.show();
    std::cout << li4.size() << "\n";
    std::cout << std::format("li4 is empty ? {}", li4.empty()) << "\n";
    std::cout << li3.front() << "\n";
    std::cout << li3.back() << "\n";

    ds::list<std::string> li5;
    std::vector<std::string> names{"zhangsan", "lisi", "wangwu", "zhaoliu"};
    li5.insert(li5.begin(), names.begin(), names.end());
    li5.push_back("老三");
    li5.push_front("老四");
    li5.show();
    li5.pop_back();
    li5.pop_front();
    li5.show();

    ds::list<std::string> li6(li5);
    li6 = li5;
    li6.show();
    ds::list<std::string> li7(std::move(li6));
    li7.show();

    ds::list<std::string> li8;
    li8 = std::move(li7);
    li8.show();

    ds::list<int> li9{0, 1, 2, 3, 4, 5};
    li9.show();
}


int main()
{
    test_list();
    std::vector<int> vec;
    std::list<int> li;
    std::string str;
    return 0;
}