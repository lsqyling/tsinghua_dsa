//
// Created by shiqing on 19-5-18.
//

#include "dsa/CommonHeaders.h"
#include "dsa/Vector.h"
#include "dsa/String.h"


using namespace linear;

void testingConstructing()
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
}

void testingReadAndWriteVector()
{
    Vector<int> vi;
    for (int i = 0; i != 1024; ++i)
    {
        vi.pushBack(0 + i);
    }
    cout << vi << endl;

    vi.erase(511, 1024 - 511);
    cout << vi << endl;
    vi.erase(11, 211);
    cout << vi << endl;
    vi.erase(vi.begin() + 10, vi.end());
    cout << vi << endl;

    vi.insert(10, 10);
    cout << vi << endl;
    vi.insert(vi.begin(), -1);
    vi.insert(vi.end(), 11);
    cout << vi << endl;

    for (int j = 0; j != 5; ++j)
    {
        cout << vi.popBack() << " ";
    }
    cout << endl;
    cout << vi << endl;
    cout << "--------------------" << endl;
    vi.emplaceBack(2);
    cout << vi << endl;
    cout << "--------------------" << endl;

}

void testingStr()
{
    char arr[35] = {"abcdefghijklmnopqrstuvwxyz"};
    String string1(arr);
    cout << string1 << endl;
    const char *cp = "hello, world!!!";
    String str = cp;
    cout << cp << endl;

    cout << "sizeof(String): " << sizeof(String) << endl;
    cout << "sizeof(string): " << sizeof(string) << endl;
    cout << std::format("sizeof(str) = {}", sizeof(str)) << std::endl;
}

void testingAlg()
{
    Vector<int> vi = {9, 1, 8, 6, 2, 3, 4, 7, 5, 0, 11, 10};
    vi.sort();
    cout << vi.find(12) << endl;
    cout << vi.search(12) << endl;
    cout << vi << endl;

    Vector<int> v{0, 1, 1, 2, 2, 2, 3, 3, 4};
    v.duplicate();
    cout << v << endl;
    vi.duplicate();
    cout << vi << endl;

    Vector<int> vvi;
    for (int i = 0; i != 1024; ++i)
    {
        vvi.pushBack(i);
        vvi.pushBack(i);
        vvi.pushBack(i);
        vvi.pushBack(i);
        vvi.pushBack(i);
    }
    vvi.uniquely();
    cout << vvi << endl;

    Vector<int> v2{1, 0};
    v2.sort();
    cout << "v2: " << v2 << endl;

}

Vector<int> getInts()
{
    return {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
}

void testingAssign()
{
//    getInts() = {0, 1, 2, 3};
    Vector<int> vi;
    vi = getInts();
    printContainer(cout, vi) << endl;
}


namespace deduction {

template<typename T>
void deductionValue(T t)
{
    auto sz = sizeof(t);
    cout << sz << " " << "T: " << typeid(T).name()
         << " t: " << typeid(t).name()
         << endl;
}

template<typename T>
void deductionReference(T &t)
{
    auto sz = sizeof(t);
    cout << sz << " " << "T: " << typeid(T).name()
         << " t: " << typeid(t).name()
         << endl;
}

template<typename T>
void deductionConstReference(const T &t)
{
    auto sz = sizeof(t);
    cout << sz << " " << "T: " << typeid(T).name()
         << " t: " << typeid(t).name()
         << endl;
}

template<typename T>
void deductionRReference(T &&t)
{
    auto sz = sizeof(t);
    cout << sz << " " << "T: " << typeid(T).name()
         << " t: " << typeid(t).name()
         << endl;
}

template<typename T>
void deductionPointer(T *t)
{
    auto sz = sizeof(t);
    cout << sz << " " << "T: " << typeid(T).name()
         << " t: " << typeid(t).name()
         << endl;
}

template<typename T>
void deductionPointerConst(const T *t)
{
    auto sz = sizeof(t);
    cout << sz << " " << "T: " << typeid(T).name()
         << " t: " << typeid(t).name()
         << endl;
}

template<typename T>
void deductionConstPointerConst(const T *const t)
{
    auto sz = sizeof(t);
    cout << sz << " " << "T: " << typeid(T).name()
         << " t: " << typeid(t).name()
         << endl;
}

void testingDeduction()
{
    int i = 42;
    int &ri = i;
    const int &cri = i;
    int &&rri = 0 + i;

    int *pi = &i;
    int *const cpi = &i;
    const int *pci = &i;
    const int *const cpci = &i;

    /*
     * top const is ignored, copy
     */
    deductionValue(24); // t = {int}     T = int
    deductionValue(i); // t = {int}      T = int
    deductionValue(ri); // t = {int}     T = int
    deductionValue(cri); // t = {int}    T = int
    deductionValue(rri); // t = {int}    T = int
    deductionValue(pi); // t = {int *}   T = int *
    deductionValue(cpi); // t = {int *}  T = int *
    deductionValue(pci); // t = {const int *} T = const int *
    deductionValue(cpci); // t = {const int *}T = const int *


//        deductionReference(24);note: candidate function [with T = int] not viable: expects an l-value for 1st argument
    deductionReference(i);// t = {int &}  T = int
    deductionReference(ri); // t = {int &} T = int
    deductionReference(cri); // t = {const int &} T = const int
    deductionReference(rri); // t = {int &} T = int
    deductionReference(pi); // t = {int *&} T = int *
    deductionReference(cpi); // t = {int *const &} T = int *const
    deductionReference(pci); // t = {const int *&} T = const int *
    deductionReference(cpci); // t = {const int *const &} T = const int *const



    deductionConstReference(24); // t = {const int &} T = int
    deductionConstReference(i);// t = {const int &}  T = int
    deductionConstReference(ri); // t = {const int &} T = int
    deductionConstReference(cri); // t = {const int &} T = int
    deductionConstReference(rri); // t = {const int &} T = int
    deductionConstReference(pi); // t = {int *const &} T = int *
    deductionConstReference(cpi); // t = {int *const &} T = int *
    deductionConstReference(pci); // t = {const int *const &} T = const int *
    deductionConstReference(cpci); // t = {const int *const &} T = const int *



    deductionRReference(24); // t = {int &&} T = int
    deductionRReference(i);// t = {int &}  T = int
    deductionRReference(ri); // t = {int &} T = int
    deductionRReference(cri); // t = {const int &} T = const int
    deductionRReference(rri); // t = {int &} T = int
    deductionRReference(pi); // t = {int *&} T = int *
    deductionRReference(cpi); // t = {int *const &} T = int *const
    deductionRReference(pci); // t = {const int * &} T = const int *
    deductionRReference(cpci); // t = {const int *const &} T = const int *const


//        deductionPointer(24); note: candidate template ignored: could not match 'T *' against 'int'
//        deductionPointer(i);note: candidate template ignored: could not match 'T *' against 'int'
//        deductionPointer(ri); note: candidate template ignored: could not match 'T *' against 'int'
//        deductionPointer(cri); note: candidate template ignored: could not match 'T *' against 'int'
//        deductionPointer(rri); note: candidate template ignored: could not match 'T *' against 'int'
    deductionPointer(pi); // t = {int *} T = int
    deductionPointer(cpi); // t = {int *} T = int *
    deductionPointer(pci); // t = {const int * } T = const int *
    deductionPointer(cpci); // t = {const int *const } T = const int *


//        deductionPointerConst(24); error: no matching function for call to 'deductionPointerConst'
//        deductionPointerConst(i); error: no matching function for call to 'deductionPointerConst'
//        deductionPointerConst(ri); error: no matching function for call to 'deductionPointerConst'
//        deductionPointerConst(cri);error: no matching function for call to 'deductionPointerConst'
//        deductionPointerConst(rri); error: no matching function for call to 'deductionPointerConst'
    deductionPointerConst(pi); // t = {const int *} T = const int *
    deductionPointerConst(cpi); // t = {const int *} T = const int*
    deductionPointerConst(pci); // t = {const int *} T = const int *
    deductionPointerConst(cpci); // t = {const int *} T = const int *



//        deductionConstPointerConst(24);
//        deductionConstPointerConst(i);
//        deductionConstPointerConst(ri);
//        deductionConstPointerConst(cri);
//        deductionConstPointerConst(rri);
    deductionConstPointerConst(pi); // t = {const int *const} T = const int *const
    deductionConstPointerConst(cpi); // t = {const int *const} T = const int *const
    deductionConstPointerConst(pci); // t = {const int *const} T = const int *const
    deductionConstPointerConst(cpci); // t = {const int *const} T = const int *const

}

void testingMerge()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 3, 8, 9, 11, 21};
    using namespace linear;
    helperV::bubbleSort(0, 13, arr);

    for (const auto &item : arr)
    {
        cout << item << " ";
    }

}

void testingPrintCharStr()
{
    String s("hellworld!!!");
    cout << s.size() << endl;
    String cs(s.c_str());
    cout << cs << endl;
    cout << cs.size() << endl;
}

}

void testingStringIndexOf()
{
    String s("hello, world"), s2("world");
    cout << s.indexOf(s2) << endl;
    cout << indexOf(s, s2) << endl;
    cout << indexOfUsingKMP(s, s2) << endl;

}

void testingDestroy()
{
    auto p1 = new int(0),
            p2 = new int(1),
            p3 = new int(2),
            p4 = new int(3),
            p5 = new int(4);
    {
        std::vector<int *> vptr;
        vptr.push_back(p1);
        vptr.push_back(p2);
        vptr.push_back(p3);
        vptr.push_back(p4);
        vptr.push_back(p5);
        Vector<int *> myVptr;
        myVptr.pushBack(p1);
        myVptr.pushBack(p2);
        myVptr.pushBack(p3);
        myVptr.pushBack(p4);
        myVptr.pushBack(p5);
    }
    cout << "*p1 = " << *p1 << endl;
    cout << "*p2 = " << *p2 << endl;
    cout << "*p3 = " << *p3 << endl;
    cout << "*p4 = " << *p4 << endl;
    cout << "*p5 = " << *p5 << endl;
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete p5;
}

void testingSizeofStrAndVector()
{
    printf("sizeof(String) = %lu\n", sizeof(String));
    printf("sizeof(Vector) = %lu\n", sizeof(Vector<int>));
}

int main()
{
    deduction::testingMerge();
    deduction::testingDeduction();
    testingConstructing();
    testingReadAndWriteVector();
    testingStr();
    testingAlg();
    deduction::testingPrintCharStr();
    cout << "------------------------" << endl;
    testingStringIndexOf();
    cout << "------------------------" << endl;
    testingAssign();
    cout << "------------------------" << endl;
    testingDestroy();
    cout << "------------------------" << endl;
    testingSizeofStrAndVector();


    return 0;
}