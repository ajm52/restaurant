#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "MenuEntryKey.cpp"

#include "MenuEntryKey_T.h"

using namespace boost::unit_test;

/**
 * Unit test for MenuEntryKey.
 * author: ajm
 * created: 2/12/20
 * last modified: 2/28/20
 **/

void MenuEntryKey_T::test_case1()
{ //mek with default args.
    MenuEntryKey mek;
    BOOST_CHECK(&mek);
    BOOST_TEST(mek.getNum() == 0);
    BOOST_TEST(mek.getType() == '!');
}

void MenuEntryKey_T::test_case2()
{ //mek with args provided.
    MenuEntryKey mek('F', 2);
    BOOST_CHECK(&mek);
    BOOST_TEST(mek.getType() == 'F');
    BOOST_TEST(mek.getNum() == 2);
}

void MenuEntryKey_T::test_case3()
{ //testing copy control.
    MenuEntryKey mek1('D', 3);
    MenuEntryKey mek2(mek1);
    BOOST_REQUIRE_EQUAL(mek2, mek1);
    MenuEntryKey mek3;
    BOOST_REQUIRE_NE(mek3, mek1);
    mek3 = mek2;
    BOOST_REQUIRE_EQUAL(mek3, mek1);
}

void MenuEntryKey_T::test_case4()
{ //testing factory method.
    std::shared_ptr<MenuEntryKey> pMek = makeMenuEntryKey('F', 1);
    BOOST_TEST(pMek.get()->getNum() == 1);
    BOOST_TEST(pMek.get()->getType() == 'F');
}

test_suite *MenuEntryKey_T::init_test_suite()
{
    test_suite *ts = BOOST_TEST_SUITE("menu_entry_key_test_suite");
    ts->add(BOOST_TEST_CASE(&MenuEntryKey_T::test_case1));
    ts->add(BOOST_TEST_CASE(&MenuEntryKey_T::test_case2));
    ts->add(BOOST_TEST_CASE(&MenuEntryKey_T::test_case3));
    ts->add(BOOST_TEST_CASE(&MenuEntryKey_T::test_case4));
    framework::master_test_suite().add(ts);
    return 0;
}
