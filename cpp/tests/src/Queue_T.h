#ifndef QUEUE_T
#define QUEUE_T

#include <boost/test/unit_test.hpp>

class Queue_T
{
public:
    static boost::unit_test::test_suite *init_test_suite();

private:
    static void test_case1();
    static void test_case2();
    static void test_case3();
};

#endif // QUEUE_T