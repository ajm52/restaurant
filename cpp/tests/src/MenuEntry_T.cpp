#define BOOST_TEST_MODULE MenuEntry_Test
#include <boost/test/included/unit_test.hpp>
#include "MenuEntry.cpp"

/**
 * Unit test for MenuEntry.
 * author: ajm
 * created: 2/12/20
 * last modified: 2/12/20
 **/

BOOST_AUTO_TEST_SUITE(menuEntry_test_suite)

BOOST_AUTO_TEST_CASE(case1)
{ //me with default args.
    MenuEntry me;
    BOOST_CHECK(&me);
    BOOST_TEST(me.getName() == "");
    BOOST_TEST(me.getPrepTime() == 0);
}

BOOST_AUTO_TEST_CASE(case2)
{ //me with args provided.
    MenuEntry me("cheeseburger", 10);
    BOOST_CHECK(&me);
    BOOST_TEST(me.getName() == "cheeseburger");
    BOOST_TEST(me.getPrepTime() == 10);
}

BOOST_AUTO_TEST_CASE(case3)
{ //testing copy control.
    MenuEntry me1("onion soup", 5);
    MenuEntry me2(me1);
    MenuEntry me3;

    BOOST_TEST(me2.getName() == me1.getName());
    BOOST_TEST(me2.getPrepTime() == me1.getPrepTime());
    BOOST_TEST(me3.getName() != me2.getName());
    BOOST_TEST(me3.getPrepTime() != me2.getPrepTime());

    me3 = me1;

    BOOST_TEST(me3.getName() == me2.getName());
    BOOST_TEST(me3.getPrepTime() == me2.getPrepTime());
}

BOOST_AUTO_TEST_CASE(case4)
{ //testing factory method.
    std::shared_ptr<MenuEntry> pMe = makeMenuEntry("some food", 20);
    BOOST_TEST(pMe.get()->getName() == "some food");
    BOOST_TEST(pMe.get()->getPrepTime() == 20);
}

BOOST_AUTO_TEST_SUITE_END()