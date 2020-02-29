#define BOOST_TEST_MODULE WorkerNode_Test

#include <boost/test/included/unit_test.hpp>
#include "WorkerNode.cpp"

/**
 * Unit test for WorkerNode.
 * author ajm
 * created: 2/24/20
 * modified: 2/28/20
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

BOOST_AUTO_TEST_CASE(case3)
{ // '<=' with different and equal job counts
    WorkerNode w0("W0");
    WorkerNode w1("W1");
    w0.numJobs_ = 0;
    w1.numJobs_ = 1;
    BOOST_CHECK_LE(w0, w1);
    w1.numJobs_ = 0;
    w1.workerID_ = w0.workerID_;
    BOOST_CHECK_LE(w0, w1);
}

BOOST_AUTO_TEST_CASE(case4)
{ // '==' with different worker ids
    WorkerNode w0("W0");
    WorkerNode w1("W0");
    w0.numJobs_ = 0;
    w1.numJobs_ = 0;
    BOOST_CHECK_EQUAL(w0, w1);
    w1.workerID_ = "W1";
    BOOST_CHECK_NE(w0, w1);
}

BOOST_AUTO_TEST_CASE(case5)
{ // testing '+=' and '-='
    WorkerNode w0("W0");
    w0.numJobs_ = 3;
    w0 += 2;
    BOOST_TEST(w0.numJobs_ == 5);
    w0 -= 5;
    BOOST_TEST(w0.numJobs_ == 0);
}

BOOST_AUTO_TEST_SUITE_END()