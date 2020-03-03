#define BOOST_TEST_DYN_LINK

#include "MenuEntry_T.h"
#include "MenuEntry.cpp"
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

/**
 * Unit test for MenuEntry.
 * author: ajm
 * created: 2/12/20
 * last modified: 3/2/20
 **/

void MenuEntry_T::test_case1()
{ //me with default args.
    MenuEntry me;
    BOOST_CHECK(&me);
    BOOST_TEST(me.getName() == "");
    BOOST_TEST(me.getPrepTime() == 0);
}

void MenuEntry_T::test_case2()
{ //me with args provided.
    MenuEntry me("cheeseburger", 10);
    BOOST_CHECK(&me);
    BOOST_TEST(me.getName() == "cheeseburger");
    BOOST_TEST(me.getPrepTime() == 10);
}

void MenuEntry_T::test_case3()
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

void MenuEntry_T::test_case4()
{ //testing factory method.
    std::shared_ptr<MenuEntry> pMe = makeMenuEntry("some food", 20);
    BOOST_TEST(pMe.get()->getName() == "some food");
    BOOST_TEST(pMe.get()->getPrepTime() == 20);
}

test_suite *MenuEntry_T::init_test_suite()
{
    test_suite *ts = BOOST_TEST_SUITE("menu_entry_test_suite");
    ts->add(BOOST_TEST_CASE(&MenuEntry_T::test_case1));
    ts->add(BOOST_TEST_CASE(&MenuEntry_T::test_case2));
    ts->add(BOOST_TEST_CASE(&MenuEntry_T::test_case3));
    ts->add(BOOST_TEST_CASE(&MenuEntry_T::test_case4));
    framework::master_test_suite().add(ts);
    return 0;
}
