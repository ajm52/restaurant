#ifndef WORKERNODE_T_H
#define WORKERNODE_T_H

#include <boost/test/unit_test.hpp>

class WorkerNode_T
{
public:
    static boost::unit_test::test_suite *init_test_suite();

private:
    static void test_case1();
    static void test_case2();
    static void test_case3();
    static void test_case4();
    static void test_case5();
};

#endif // WORKERNODE_T_H