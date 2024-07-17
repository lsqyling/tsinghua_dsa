//
// Created by shiqing on 19-7-29.


#include <cassert>
#include "../../common/CommonHeaders.h"

template<typename T>
void deductionPtr(T *p)
{
};

template<typename T>
void deductionPtr2Const(const T *pc)
{
    cout << typeid(T).name() << endl;
}

template<typename E>
constexpr std::underlying_type_t<E> toUType(E enumerator) noexcept
{
    return static_cast<std::underlying_type_t<E>>(enumerator);
}

bool isLucky(int number)
{
    return !number % 7;
}

bool isLucky(char) = delete;

bool isLucky(bool) = delete;

bool isLucky(double) = delete;

void testingIsLucky()
{
    cout << isLucky(7) << endl;
}

class Point
{
public:

    Point() : x_(0), y_(0)
    {
    }

    Point(double x, double y) : x_(x), y_(y)
    {
    }

//    Point(Point &&rhs) : x_(rhs.x_), y_(rhs.y_) {}
    ~Point() = default;

private:
    double x_, y_;
};

void testingPoint()
{
    Point p(3, 5);
    Point p1;

//    p1 = std::move(p);
    p1 = p;
    Point p2(p1);

    std::shared_ptr<int> sPtr2I = std::make_shared<int>(42);
    cout << sizeof(sPtr2I) << endl;

}

int main(int argc, char *argv[])
{
    int d = 42;
    int *pd = &d;
    const int *pcd = &d;

    const int *const cpcd = &d;

    deductionPtr(pd);
    deductionPtr(pcd);
    deductionPtr(cpcd);

    deductionPtr2Const(pd);
    deductionPtr2Const(pcd);
    deductionPtr2Const(cpcd);
    testingIsLucky();
    testingPoint();

    return 0;
}





















