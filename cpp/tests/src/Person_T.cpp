#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "Person.h"

#include "Person_T.h"

using namespace boost::unit_test;

/**
 * Unit test for Person.h
 * author: ajm
 * created: 1/30/20
 * last modified: 2/28/20
 **/

void Person_T::test_case1()
{ //Person with default id arg
    Person p;
    BOOST_CHECK(&p); //ensures p is not null
    BOOST_TEST(p.getId() == "DEFAULT_PID");
}

void Person_T::test_case2()
{ //Person with provided id arg
    Person p("Some id");
    BOOST_CHECK(&p);
    BOOST_TEST(p.getId() == "Some id");
}

test_suite *Person_T::init_test_suite()
{
    test_suite *ts = BOOST_TEST_SUITE("person_test_suite");
    ts->add(BOOST_TEST_CASE(&Person_T::test_case1));
    ts->add(BOOST_TEST_CASE(&Person_T::test_case2));
    framework::master_test_suite().add(ts);
    return 0;
}
