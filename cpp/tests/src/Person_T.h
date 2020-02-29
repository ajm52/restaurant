#ifndef PERSON_T_H
#define PERSON_T_H

#include <boost/test/unit_test.hpp>

class Person_T
{
public:
    static boost::unit_test::test_suite *init_test_suite();

private:
    static void test_case1();
    static void test_case2();
};

#endif // PERSON_T_H