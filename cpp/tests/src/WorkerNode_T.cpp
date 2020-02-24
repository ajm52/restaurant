#define BOOST_TEST_MODULE WorkerNode_Test

#include <boost/test/included/unit_test.hpp>
#include "WorkerNode.h"

/**
 * Unit test for WorkerNode.
 * author ajm
 * created: 2/24/20
 * modified: 2/24/20
 */

BOOST_AUTO_TEST_SUITE(workernode_test_suite)

BOOST_AUTO_TEST_CASE(case1)
{ // testing '<' operator with different job counts
    WorkerNode w0("W0");
    WorkerNode w1("W1");
    w0.numJobs_ = 2;
    w1.numJobs_ = 0;
    BOOST_CHECK(&w0);
    BOOST_CHECK(&w1);
    BOOST_CHECK_LT(w1, w0);
}

BOOST_AUTO_TEST_CASE(case2)
{ // testing '<' with equal job counts
    WorkerNode w0("W0");
    WorkerNode w1("W1");
    w0.numJobs_ = 1;
    w1.numJobs_ = 1;
    BOOST_CHECK(&w0);
    BOOST_CHECK(&w1);
    BOOST_CHECK_LT(w0, w1);
}

BOOST_AUTO_TEST_SUITE_END()