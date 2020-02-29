#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "WorkerNode.cpp"

#include "WorkerNode_T.h"

using namespace boost::unit_test;

/**
 * Unit test for WorkerNode.
 * author ajm
 * created: 2/24/20
 * modified: 2/28/20
 */

void WorkerNode_T::test_case1()
{ // testing '<' operator with different job counts
    WorkerNode w0("W0");
    WorkerNode w1("W1");
    w0.numJobs_ = 2;
    w1.numJobs_ = 0;
    BOOST_CHECK(&w0);
    BOOST_CHECK(&w1);
    BOOST_CHECK_LT(w1, w0);
}

void WorkerNode_T::test_case2()
{ // testing '<' with equal job counts
    WorkerNode w0("W0");
    WorkerNode w1("W1");
    w0.numJobs_ = 1;
    w1.numJobs_ = 1;
    BOOST_CHECK(&w0);
    BOOST_CHECK(&w1);
    BOOST_CHECK_LT(w0, w1);
}

void WorkerNode_T::test_case3()
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

void WorkerNode_T::test_case4()
{ // '==' with different worker ids
    WorkerNode w0("W0");
    WorkerNode w1("W0");
    w0.numJobs_ = 0;
    w1.numJobs_ = 0;
    BOOST_CHECK_EQUAL(w0, w1);
    w1.workerID_ = "W1";
    BOOST_CHECK_NE(w0, w1);
}

void WorkerNode_T::test_case5()
{ // testing '+=' and '-='
    WorkerNode w0("W0");
    w0.numJobs_ = 3;
    w0 += 2;
    BOOST_TEST(w0.numJobs_ == 5);
    w0 -= 5;
    BOOST_TEST(w0.numJobs_ == 0);
}

test_suite *WorkerNode_T::init_test_suite()
{
    test_suite *ts = BOOST_TEST_SUITE("worker_node_test_suite");
    ts->add(BOOST_TEST_CASE(&WorkerNode_T::test_case1));
    ts->add(BOOST_TEST_CASE(&WorkerNode_T::test_case2));
    ts->add(BOOST_TEST_CASE(&WorkerNode_T::test_case3));
    ts->add(BOOST_TEST_CASE(&WorkerNode_T::test_case4));
    ts->add(BOOST_TEST_CASE(&WorkerNode_T::test_case5));
    framework::master_test_suite().add(ts);
    return 0;
}
