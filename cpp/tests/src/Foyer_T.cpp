#define BOOST_TEST_DYN_LINK

#include "Foyer_T.h"
#include "Party.cpp"
#include "Foyer.cpp"
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

/**
 * Unit test for Foyer
 * author: ajm
 * created: 3/2/20
 * modified: 3/2/20
 */
void Foyer_T::test_case1()
{ // test party insertions and removals
    BOOST_TEST_CHECKPOINT("starting foyer_test_suite");
    Foyer f;
    Party *p1 = new Party("P1");
    Party *p2 = new Party("P2");
    Party *p3 = new Party("P3");
    //insertions
    BOOST_TEST(f.putParty(3, p1));
    BOOST_TEST(!f.putParty(3, p2));
    BOOST_TEST(f.putParty(1, p3));
    //removals
    BOOST_TEST(f.removeParty(4) == nullptr);
    BOOST_TEST(f.removeParty(3) == p1);
    //cleanup
    delete p1;
    delete p2;
    delete p3;
}

test_suite *Foyer_T::init_test_suite()
{
    test_suite *ts = BOOST_TEST_SUITE("foyer_test_suite");
    ts->add(BOOST_TEST_CASE(&Foyer_T::test_case1));
    framework::master_test_suite().add(ts);
    return 0;
}