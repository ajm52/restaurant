#define BOOST_TEST_MODULE Person_Test
#include <boost/test/included/unit_test.hpp>
#include "Person.h"

/**
 * Unit test for Person.cpp
 * author: ajm
 **/

BOOST_AUTO_TEST_SUITE(person_test_suite)

BOOST_AUTO_TEST_CASE(case1)
{ //Person with default ctor
    Person p;
    BOOST_CHECK(&p); //ensures p is not null
    BOOST_TEST(p.getId() == "DEFAULT_PID");
}

BOOST_AUTO_TEST_CASE(case2)
{ //Person with other ctor
    Person p("Some id");
    BOOST_CHECK(&p);
    BOOST_TEST(p.getId() == "Some id");
}

BOOST_AUTO_TEST_CASE(case3)
{ //const Person (testing const accessor)
    const Person p("Some id");
    BOOST_TEST(p.getId() == "Some id");
}

BOOST_AUTO_TEST_CASE(case4)
{ //ensuring that Person cannot be copied
    BOOST_TEST(std::is_copy_constructible<Person>::value == 0);
    BOOST_TEST(std::is_copy_assignable<Person>::value == 0);
}

BOOST_AUTO_TEST_SUITE_END()