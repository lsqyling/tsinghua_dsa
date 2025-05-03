#include <iostream>
#include <vector>
#include <array>
#include "dsa/vector.hpp"

void test_vector()
{
    ds::vector<int> v0;
    std::cout << std::format("dtor is noexcept? {}\n", noexcept(v0.~vector<int>()));
    v0.show();

    ds::vector<int> v1(3, 5);
    v1.show();

    ds::vector<int> v2(v1.begin(), v1.end());
    v2.show();

    ds::vector<std::string> v3(3, "abc");
    ds::vector<std::string> v4(v3.begin(), v3.end());
    v4.show();

    ds::vector<std::string> v5{"abc", "def", "jk", "lm"};
    v5.show();
    ds::vector<std::string> v6(v5);
    v6.show();

    ds::vector<std::string> v7(std::move(v6));
    v7.show();
    v7.swap(v6);
    v7.show();

    v5.reserve(10);
    v5.show();
    v5.reserve(2);
    v5.show();

    ds::vector<int> v8{0, 1, 2};
    ds::vector<int> v9{3, 4, 5, 6};
    v8 = v9;
    v8.show();
    v8.reserve(9);
    v8.show();
    ds::vector<int> v10{0, 1, 2, 3, 4};
    v8 = v10;
    v8.show();
    ds::vector<int> v11{0, 1, 2};
    v8 = v11;
    v8.show();

    ds::vector<int> v12;
    v12 = ds::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8};
    v12.show();
    std::cout << std::format("front: {}, back: {}\n", v12.front(), v12.back());
    v12.clear();
    std::cout << std::format("v12 is empty ? {}\n", v12.empty());
    const ds::vector<int> v13{0, 1, 2, 3, 4, 5, 6, 7, 8};
    std::cout << std::format("const_front: {}, const_back: {}\n", v13.front(), v13.back());
}

void test_insert_erase()
{
    ds::vector<std::string> v0{"3", "3", "3", "3"};
    v0.reserve(9);
    v0.show();
    v0.insert(v0.begin() + 1, 2, "5");
    v0.show();

    v0.insert(v0.begin() + 4, 2, "6");
    v0.show();
    v0.insert(v0.begin() + 5, 10, "7");
    v0.show();

    ds::vector<std::string> v1{"11", "22", "33"};
    v1.insert(v1.end(), "44");
    v1.show();
    v1.insert(v1.begin() + 1, "55");
    v1.insert(v1.begin(), "66");
    v1.show();
    v1.insert(v1.begin(), "77");
    v1.show();
    v1.insert(v1.end(), "88");
    v1.show();
    std::string s{"99"};
    v1.insert(v1.begin(), s);
    v1.show();
    v1.erase(v1.begin() + 2, v1.end() - 2);
    v1.show();
}

void test_push_pop()
{
    ds::vector<int> v0;
    for (int i = 0; i < 10; ++i) {
        v0.push_back(i);
    }
    v0.push_back(10);
    v0.show();

    v0.pop_back();
    v0.show();
    v0.resize(8);
    v0.show();
    v0.resize(9);
    v0.show();
}


int main()
{
    test_vector();
    test_insert_erase();
    test_push_pop();
    std::array<int, 3> arr;
    return 0;
}