## Tsinghua-DataStructure
[![License](https://img.shields.io/badge/License-Apache%202.0-green.svg)](https://github.com/lsqyling/tsinghua_dsa/blob/main/LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Linux-blue)](https://img.shields.io/badge/Platform-Linux-blue)
[![Windows](https://img.shields.io/badge/Windows-blue)](https://img.shields.io/badge/Windows-blue)
[![Language](https://img.shields.io/badge/Language-C%2B%2B20-red)](https://en.cppreference.com/w/cpp/compiler_support/20)

**简介：这是清华邓俊辉老师的数据结构课程，同时也是考研912的核心课程。该项目是在课程的主导下的项目，在不断完善中希望能
独立成为一个数据结构常用库。**

### Part1. 理论部分
- 项目结构：include/dsa | src/dsa
- 第一阶段：绪论计算理论部分
- 第二阶段：线性数据结构
- 第三阶段：树和图


### Part2. 实践部分
- 项目结构：oj/tsinghua | oj/leetcode
- 重点题目：



### Part3. 使用说明

- 1. 下载编译dsa库
```shell
git clone https://github.com/lsqyling/tsinghua_dsa.git &&
cmake -B build &&
cmake --build build -j4 --config Release --target install 
```
- 2. cmake 使用dsa库
```cmake
set(dsa_DIR xxx/tsinghua_dsa/install/lib/cmake/dsa)
# xxx ---> 命令： echo | pwd 的结果，即你下载的目录路径
find_package(dsa REQUIRED)

add_executable(hello main.cpp)
target_link_libraries(hello PRIVATE tsinghua::dsa_static)
# or
target_link_libraries(hello PRIVATE tsinghua::dsa_shared)

```
- 3. main.cpp
```c++
#include <iostream>
#include <dsa/Vector.h>
#include <dsa/CommonHeaders.h>
#include <dsa/String.h>

using namespace linear;

int main()
{
    Vector<int> v1;
    cout << v1 << endl;

    Vector<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << "vi: " << vi << endl;

    Vector<int> v2(vi);
    cout << "v2: " << v2 << endl;

    Vector<int> v3(std::move(vi));
    cout << "v3: " << v3 << endl;

    Vector<int> v4(10, 1);
    cout << "v4: " << v4 << endl;

    auto beg = v3.begin(), end = v3.end();
    Vector<int> v5(beg, end);
    cout << "v5: " << v5 << endl;

    int i = 2;
    Vector<int> v6(10, i);
    cout << "v6: " << v6 << endl;
    cout << "v6 is empty? " << v6.empty() << endl;

    cout << (v6 == v5) << endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

```