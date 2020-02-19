#define BOOST_TEST_MODULE Menu_Test

#include "MenuEntryKey.cpp"
#include "MenuEntry.cpp"
#include "Menu.cpp"
#include <boost/test/included/unit_test.hpp>
#include <iterator>

/**
 * Unit test for Menu.
 * author: ajm
 * created: 2/12/20
 * last modified: 2/19/20
 **/
BOOST_AUTO_TEST_SUITE(menu_test_suite)

static std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator> opts = {
    {MenuEntryKey('F', 0), MenuEntry("burger", 10)},
    {MenuEntryKey('F', 1), MenuEntry("fish", 15)},
    {MenuEntryKey('F', 2), MenuEntry("fries", 5)},

    {MenuEntryKey('D', 0), MenuEntry("water", 1)},
    {MenuEntryKey('D', 1), MenuEntry("soda", 3)}};

unsigned numF = 3, numD = 2;

BOOST_AUTO_TEST_CASE(case1)
{ //m with default args.
    Menu m;
    BOOST_CHECK(&m);
    BOOST_TEST(m.getOptions().size() == 0);
    BOOST_TEST(m.getNumFoodOptions() == 0);
    BOOST_TEST(m.getNumDrinkOptions() == 0);
}

BOOST_AUTO_TEST_CASE(case2)
{ //m with args provided.
    Menu m(opts);
    BOOST_CHECK(&m);
    BOOST_TEST(m.getNumFoodOptions() == numF);
    BOOST_TEST(m.getNumDrinkOptions() == numD);

    std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator>::const_iterator itr = m.getOptions().begin();
    while (itr != m.getOptions().end())
    {
        BOOST_TEST(itr->second.getName() == opts[itr->first].getName());
        BOOST_TEST(itr->second.getPrepTime() == opts[itr->first].getPrepTime());
        ++itr;
    }
}

BOOST_AUTO_TEST_CASE(case3)
{ //testing copy control.
    BOOST_TEST(std::is_copy_constructible<Menu>::value == 0);
    BOOST_TEST(std::is_copy_assignable<Menu>::value == 0);
}

BOOST_AUTO_TEST_SUITE_END()