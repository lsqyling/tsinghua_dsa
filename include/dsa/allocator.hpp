//
// Created by 10580.
//

#ifndef TSINGHUA_DSA_INCLUDE_DSA_ALLOCATOR_HPP
#define TSINGHUA_DSA_INCLUDE_DSA_ALLOCATOR_HPP
#include <cstddef>
#include <memory>
namespace ds {
template<typename T>
class allocator
{
public:
    using value_type      = T;
    using pointer         = value_type *;
    using reference       = value_type &;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

    static pointer allocate(const size_type n = 1)
    {
        return static_cast<pointer >(::operator new(n * sizeof(value_type)));
    }
    static void deallocate(pointer ptr)
    {
        ::operator delete(ptr);
    }
    static void construct(pointer ptr, const value_type &val)
    {
        new(ptr) value_type (val);
    }
    static void destroy(pointer ptr)
    {
        ptr->~value_type();
    }
};

























}

#endif //TSINGHUA_DSA_INCLUDE_DSA_ALLOCATOR_HPP
