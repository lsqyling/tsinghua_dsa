#include "dsa/hash_table.hpp"
#include <list>

void test_ht()
{
    ds::hash_table<std::string, std::string, std::hash<std::string>, std::identity> ht;
    ht.insert(std::string("Bob"));
    ht.insert(std::string("Alice"));
    ht.insert(std::string("Banana"));
    ht.insert(std::string("Mark"));

    auto it = ht.find(std::string("Mark"));
    std::cout << *it << std::endl;
}





















int main()
{
//    test_ht();
    return 0;
}