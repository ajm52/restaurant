#ifndef ORDER_T_H
#define ORDER_T_H

#include <boost/test/unit_test.hpp>

class Order_T
{
public:
    static boost::unit_test::test_suite *init_test_suite();

private:
    static void test_case1();
    static void test_case2();
};

#endif // ORDER_T_H