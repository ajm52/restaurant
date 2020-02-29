#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "Guest.h"

#include "Guest_T.h"

using namespace boost::unit_test;

/**
 * Unit test for Guest.h
 * author: ajm
 * created: 2/3/20
 * last modified: 2/28/20
 **/
void Guest_T::test_case1()
{ //Guest with default id arg
    Guest g;
    BOOST_CHECK(&g); //check if null
    BOOST_TEST(g.getId() == "DEFAULT_GID");
}

void Guest_T::test_case2()
{ //Guest with provided id arg
    Guest g(std::string("Some guest"));
    BOOST_CHECK(&g);
    BOOST_TEST(g.getId() == "Some guest");
}

void Guest_T::test_case3()
{ //ensuring Guest cannot be copied
    BOOST_TEST(std::is_copy_constructible<Guest>::value == 0);
    BOOST_TEST(std::is_copy_assignable<Guest>::value == 0);
}

test_suite *Guest_T::init_test_suite()
{
    test_suite *ts = BOOST_TEST_SUITE("guest_test_suite");
    ts->add(BOOST_TEST_CASE(&Guest_T::test_case1));
    ts->add(BOOST_TEST_CASE(&Guest_T::test_case2));
    ts->add(BOOST_TEST_CASE(&Guest_T::test_case3));
    framework::master_test_suite().add(ts);
    return 0;
}
