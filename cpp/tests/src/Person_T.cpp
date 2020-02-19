#define BOOST_TEST_MODULE Person_Test
#include <boost/test/included/unit_test.hpp>
#include "Person.h"

/**
 * Unit test for Person.h
 * author: ajm
 * created: 1/30/20
 * last modified: 2/19/20
 **/

BOOST_AUTO_TEST_SUITE(person_test_suite)

BOOST_AUTO_TEST_CASE(case1)
{ //Person with default id arg
    Person p;
    BOOST_CHECK(&p); //ensures p is not null
    BOOST_TEST(p.getId() == "DEFAULT_PID");
}

BOOST_AUTO_TEST_CASE(case2)
{ //Person with provided id arg
    Person p("Some id");
    BOOST_CHECK(&p);
    BOOST_TEST(p.getId() == "Some id");
}

BOOST_AUTO_TEST_SUITE_END()