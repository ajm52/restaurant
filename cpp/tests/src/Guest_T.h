#ifndef GUEST_T_H
#define GUEST_T_H

#include <boost/test/unit_test.hpp>

class Guest_T
{
public:
    static boost::unit_test::test_suite *init_test_suite();

private:
    static void test_case1();
    static void test_case2();
    static void test_case3();
};

#endif // GUEST_T_H