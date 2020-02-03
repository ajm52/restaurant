#define BOOST_TEST_MODULE Guest_Test
#include <boost/test/included/unit_test.hpp>
#include "Guest.h"

/**
 * Unit test for Guest.h
 * author: ajm
 * created: 2/3/20
 * last modified: 2/3/20
 **/

BOOST_AUTO_TEST_SUITE(guest_test_suite)

BOOST_AUTO_TEST_CASE(case1)
{ //Guest with default id arg
    Guest g;
    BOOST_CHECK(&g); //check if null
    BOOST_TEST(g.getId() == "DEFAULT_GID");
}

BOOST_AUTO_TEST_CASE(case2)
{ //Guest with provided id arg
    Guest g(std::string("Some guest"));
    BOOST_CHECK(&g);
    BOOST_TEST(g.getId() == "Some guest");
}

BOOST_AUTO_TEST_CASE(case3)
{ //ensuring Guest cannot be copied
    BOOST_TEST(std::is_copy_constructible<Guest>::value == 0);
    BOOST_TEST(std::is_copy_assignable<Guest>::value == 0);
}

//TODO: write tests for Guest's ability to use the Menu.

BOOST_AUTO_TEST_SUITE_END()