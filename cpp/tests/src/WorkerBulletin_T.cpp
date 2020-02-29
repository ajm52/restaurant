#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "WorkerBulletin.cpp"

#include "WorkerBulletin_T.h"

using namespace boost::unit_test;

/**
 * Unit test for WorkerBulletin.
 * author ajm
 * created: 2/27/20
 * modified: 2/28/20
 */

void WorkerBulletin_T::test_case1()
{
    BOOST_TEST(true);
}

test_suite *WorkerBulletin_T::init_test_suite()
{
    test_suite *ts = BOOST_TEST_SUITE("worker_bulletin_test_suite");
    ts->add(BOOST_TEST_CASE(&WorkerBulletin_T::test_case1));
    framework::master_test_suite().add(ts);
    return 0;
}
