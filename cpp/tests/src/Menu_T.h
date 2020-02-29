#ifndef MENU_T_H
#define MENU_T_H

#include <boost/test/unit_test.hpp>

class Menu_T
{
public:
    static boost::unit_test::test_suite *init_test_suite();

private:
    static void test_case1();
    static void test_case2();
    static void test_case3();
};

#endif // MENU_T_H