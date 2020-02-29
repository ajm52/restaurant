#ifndef MINHEAP_T_H
#define MINHEAP_T_H

#include <boost/test/unit_test.hpp>

class MinHeap_T
{
public:
    static boost::unit_test::test_suite *init_test_suite();

private:
    static void test_case1();
    static void test_case2();
    static void test_case3();
    static void test_case4();
    static void test_case5();
    static void test_case6();
    static void test_case7();
};

#endif // MINHEAP_T_H