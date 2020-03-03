#ifndef FOYER_T_H
#define FOYER_T_H

#include <boost/test/unit_test.hpp>

class Foyer_T
{
public:
    static boost::unit_test::test_suite *init_test_suite();

private:
    static void test_case1();
};

#endif // FOYER_T_H