#define BOOST_TEST_MODULE MenuEntryKey_Test
#include <boost/test/included/unit_test.hpp>
#include "MenuEntryKey.cpp"

/**
 * Unit test for Order.h
 * author: ajm
 * created: 2/3/20
 * last modified: 2/3/20
 **/

BOOST_AUTO_TEST_SUITE(menuEntryKey_test_suite)

std::vector<int> selections{1, 2, 3, 4};

BOOST_AUTO_TEST_CASE(case1)
{ //mek with default args.
    MenuEntryKey mek;
    BOOST_CHECK(&mek);
    BOOST_TEST(mek.getNum() == 0);
    BOOST_TEST(mek.getType() == '!');
}

BOOST_AUTO_TEST_CASE(case2)
{ //mek with args provided.
    MenuEntryKey mek('F', 2);
    BOOST_CHECK(&mek);
    BOOST_TEST(mek.getType() == 'F');
    BOOST_TEST(mek.getNum() == 2);
}

BOOST_AUTO_TEST_CASE(case3)
{ //testing copy control.
    MenuEntryKey mek1('D', 3);
    MenuEntryKey mek2(mek1);
    BOOST_REQUIRE_EQUAL(mek2, mek1);
    MenuEntryKey mek3;
    BOOST_REQUIRE_NE(mek3, mek1);
    mek3 = mek2;
    BOOST_REQUIRE_EQUAL(mek3, mek1);
}

BOOST_AUTO_TEST_CASE(case4)
{ //testing factory method.
    std::shared_ptr<MenuEntryKey> pMek = makeMenuEntryKey('F', 1);
    BOOST_TEST(pMek.get()->getNum() == 1);
    BOOST_TEST(pMek.get()->getType() == 'F');
}

BOOST_AUTO_TEST_SUITE_END()