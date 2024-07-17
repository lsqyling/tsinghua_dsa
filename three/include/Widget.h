//
// Created by shiqing on 19-7-29.
//

#ifndef TSINGHUA_DATASTRUCTURE_WIDGET_H
#define TSINGHUA_DATASTRUCTURE_WIDGET_H

#include <memory>

namespace rawp {

class Widget
{
public:
    Widget();

    ~Widget();

private:
    struct Impl;
    Impl *pImpl;

};

}

namespace up {
class Widget
{
public:
    Widget();

    Widget(Widget &&) = default;

    Widget &operator=(Widget &&) = default;

    ~Widget() = default;

private:
    struct Impl;
    std::unique_ptr<Impl> upImpl_;
};

}

namespace fwd {
template<typename T>
void logAndAdd(T &&x);
}

namespace th {

struct Triad
{
    double cos_alpha;
    double cos_beta;
    double cos_gamma;
};

struct Point
{
    double x_;
    double y_;
    double z_;
};

Point points[100][100][100];
Triad angles[100][100][100];

std::default_random_engine e;
std::uniform_real_distribution<double> u(-500.0, 500.0);

void initPoints() noexcept;

int doAsyncWord() noexcept;

}

#endif //TSINGHUA_DATASTRUCTURE_WIDGET_H
