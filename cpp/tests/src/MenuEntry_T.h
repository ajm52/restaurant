#ifndef MENUENTRY_T
#define MENUENTRY_T

#include <boost/test/unit_test.hpp>

class MenuEntry_T
{
public:
    static boost::unit_test::test_suite *init_test_suite();

private:
    static void test_case1();
    static void test_case2();
    static void test_case3();
    static void test_case4();
};

#endif // MENUENTRY_T