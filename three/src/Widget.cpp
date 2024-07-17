//
// Created by shiqing on 19-7-29.
//
#include <map>
#include <chrono>
#include <future>
#include "../../common/CommonHeaders.h"
#include "../include/Widget.h"

namespace rawp {

struct Widget::Impl
{
    std::string name_;
    std::vector<double> data_;
    std::map<std::string, std::string> mss_;
};

Widget::Widget() : pImpl(new Impl)
{
    std::cout << "Widget" << std::endl;
}

Widget::~Widget()
{
    delete pImpl;
}

void testingRawp()
{
    Widget wid;

}

}

namespace up {
struct Widget::Impl
{
    std::string name_;
    std::vector<double> data_;
    std::map<std::string, std::string> mss_;
};

Widget::Widget() : upImpl_(std::make_unique<Impl>())
{
    std::cout << "up::Wiget()" << std::endl;
}

void testingUp()
{
    Widget wid;
    Widget wid2(std::move(wid));

}

}

namespace fwd {
string nameFromIdx(int idx)
{
    return string("hello");
}

template<typename T>
void logAndImpl(T &&x, std::false_type)
{
    auto now = std::chrono::system_clock::now();
    cout << "x = " << x << ", " << now.time_since_epoch().count() << endl;
}

void logAndImpl(int idx, std::true_type)
{
    logAndAdd(nameFromIdx(idx));
}

template<typename T>
void logAndAdd(T &&x)
{
    logAndImpl(std::forward<T>(x),
               std::is_integral<std::remove_reference_t<T>>());
}

void testingLogAndAdd()
{
    string s("hello");
    int idx = 0;
    logAndAdd(s);
    logAndAdd(std::move(s));
    logAndAdd(idx);

}

template<typename T>
T &&forward(std::remove_reference_t<T> &param)
{
    return static_cast<T &&>(param);
}

template<typename T>
auto move(T &&param)
{
    return static_cast<std::remove_reference_t<T> &&>(param);
}

template<typename Container, typename Index>
decltype(auto) authAccess(Container &&c, Index index)
{
    return std::forward<Container>(c)[index];
}

void testingMoveAndFwd()
{
    string s("hello, world");
    auto d = fwd::move(s);

    string sf("world");
    auto e = fwd::forward<string>(sf);

    cout << d << endl;
    cout << s << endl;
    cout << e << endl;
    cout << sf << endl;

    std::vector<int> vi{0, 1, 2, 3, 4};
    authAccess(vi, 0) = -1;

    int &&r = 3;
    r = 4;

    decltype(fwd::move(s)) rs = string("world");
    cout << sizeof(r) << endl;

}

}

namespace person {

class Person
{
public:
    template<
            typename T,
            typename = std::enable_if_t<
                    !std::is_base_of<Person, std::decay_t<T>>()
                    &&
                    !std::is_integral<std::remove_reference_t<T>>()
            >
    >
    explicit Person(T &&x) : name_(std::forward<T>(x))
    {
        static_assert(std::is_constructible<string, T>(),
                      "Parameter n can't be used to construct a string");
    }

private:
    string name_;
};

}

namespace lambda {

using FilterContainer = std::vector<std::function<bool(int)>>;
FilterContainer filters;

class Widget
{
public:
    Widget() : divisor_(1)
    {
    }

    void addFilter() const;

private:
    int divisor_;
};

void Widget::addFilter() const
{
//        do it in c11
    /*auto copy = divisor_;
    filters.emplace_back(
            [copy](int value) { return value % copy == 0; }
            );*/

    filters.emplace_back(
            [divisor = divisor_](int value)
            { return value % divisor == 0; }
    );

}

}

namespace tie {
using Time = std::chrono::steady_clock::time_point;
using Duration = std::chrono::steady_clock::duration;

enum class Sound
{
    Beep, Siren, Whistle
};

void setAlarm(Time t, Sound s, Duration d)
{
};

auto setSound = [](Sound s)
{
    using namespace std::chrono;
    setAlarm(steady_clock::now() + hours(1), s, seconds(30));
};

auto set = [](Sound s)
{
    using namespace std::chrono;
    setAlarm(steady_clock::now() + 1h, s, 30s);
};

}

namespace th {

void initPoints() noexcept
{
    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < 100; ++j)
        {
            for (int k = 0; k < 100; ++k)
            {
                points[i][j][k] = {u(e), u(e), u(e)};
            }
        }
    }
}

int doAsyncWord() noexcept
{
    initPoints();
    Point p;
    Triad t;
    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < 100; ++j)
        {
            for (int k = 0; k < 100; ++k)
            {
                p = points[i][j][k];
                t.cos_alpha = p.x_ / (std::sqrt(p.x_ * p.x_ + p.y_ * p.y_ + p.z_ * p.z_));
                t.cos_beta = p.y_ / (std::sqrt(p.x_ * p.x_ + p.y_ * p.y_ + p.z_ * p.z_));
                t.cos_gamma = p.z_ / (std::sqrt(p.x_ * p.x_ + p.y_ * p.y_ + p.z_ * p.z_));
                angles[i][j][k] = t;
            }
        }
    }
    return 0;
}

template<typename F, typename... Args>
inline auto realAsync(F &&f, Args &&...params)
{
    return std::async(std::launch::async,
                      std::forward<F>(f),
                      std::forward<Args>(params)...);
}

void testingAsync()
{

    auto fut = realAsync(doAsyncWord);
    cout << fut.get() << endl;

    realAsync([]()
              { cout << "hello, world"; });

    std::vector<string> vs;
    vs.emplace_back("hello");
    printContainer(cout, vs) << endl;

}

}

namespace jo {

class ThreadRAII
{
public:
    enum class DtorAction
    {
        join, detach
    };

    ThreadRAII(std::thread &&t, DtorAction action) : action_(action), t_(std::move(t))
    {
    }

    ~ThreadRAII()
    {
        if (t_.joinable())
        {
            if (action_ == DtorAction::join)
            {
                t_.join();
            }
            else
            {
                t_.detach();
            }
        }
    }

    std::thread &get()
    {
        return t_;
    }

    ThreadRAII(ThreadRAII &&) = default;

    ThreadRAII &operator=(ThreadRAII &&) = default;

private:
    DtorAction action_;
    std::thread t_;
};

}

int main(int argc, char *argv[])
{
    rawp::testingRawp();
    up::testingUp();
    fwd::testingLogAndAdd();
    fwd::testingMoveAndFwd();
    th::testingAsync();
    return 0;
}