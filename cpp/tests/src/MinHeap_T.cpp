#define BOOST_TEST_DYN_LINK

#include <ostream>
#include <map>
#include <boost/test/unit_test.hpp>
#include "WorkerNode.h"
#include "MinHeap.cpp"

#include "MinHeap_T.h"

using namespace boost::unit_test;

/**
 * Unit test for MinHeap.
 * author ajm
 * created: 2/21/20
 * modified: 2/28/20
 */

void MinHeap_T::test_case1()
{ // empty heap
    MinHeap<int> h;
    BOOST_CHECK(&h);
    BOOST_TEST(h.heap_.size() == 0);
}

void MinHeap_T::test_case2()
{ // heap<int> of size 1
    MinHeap<int> h;
    int size = 1, value = 1;
    BOOST_CHECK(&h);
    h.insert(value);
    BOOST_TEST(h.heap_.size() == size);
    BOOST_TEST(h.heap_[0] == value);
}

void MinHeap_T::test_case3()
{ // heap<int> of size 5
    MinHeap<int> h;
    int size = 5;
    BOOST_CHECK(&h);
    for (int i = size; i > 0; --i)
        h.insert(i);

    BOOST_TEST(h.heap_.size() == 5);

    /**
     * following the previous order of inserts,
     * heap_ should be [1, 2, 4, 5, 3].
     * If you don't believe me, check it yourself.
     */
    int *testArray = new int[size];
    testArray[0] = 1;
    testArray[1] = 2;
    testArray[2] = 4;
    testArray[3] = 5;
    testArray[4] = 3;
    for (int i = 0; i < size; ++i)
    {
        BOOST_TEST(testArray[i] == h.heap_[i]);
    }
    delete[] testArray;
}

void MinHeap_T::test_case4()
{ // testing decr(int) w/ Heap<int> of size 3
    MinHeap<int> h;
    int size = 3;
    for (int i = 0; i < size; ++i)
    { // inserting 1, 3, 5.
        h.insert(2 * i + 1);
    }

    std::map<int, int> tracker;
    tracker[3] = 1;

    for (int i = 0; i < size; ++i)
    { // decrementing 3, 3 times.
        tracker = h.decr(tracker[3 - i]);
    }
    //h should now be [0, 1, 5]
    int *testArray = new int[size];
    testArray[0] = 0;
    testArray[1] = 1;
    testArray[2] = 5;
    for (int i = 0; i < size; ++i)
        BOOST_TEST(testArray[i] == h.heap_[i]);

    delete[] testArray;
}

void MinHeap_T::test_case5()
{ // testing incr(int) w/ Heap<int> of size 3
    MinHeap<int> h;
    int size = 3;
    for (int i = 0; i < size; ++i)
    { // inserting 1, 3, 5.
        h.insert(2 * i + 1);
    }
    std::map<int, int> tracker;
    tracker[1] = 0;

    for (int i = 0; i < size; ++i)
    { // incrementing 1, 3 times.
        tracker = h.incr(tracker[1]);
    }
    //h should now be [3, 4, 5]
    int *testArray = new int[size];
    testArray[0] = 3;
    testArray[1] = 4;
    testArray[2] = 5;
    for (int i = 0; i < size; ++i)
        BOOST_TEST(testArray[i] == h.heap_[i]);

    delete[] testArray;
}

void MinHeap_T::test_case6()
{ // testing incr(int) and decr(int) w/ Heap<WorkerNode> of size 5.
    MinHeap<WorkerNode> h;
    int size = 5;

    for (int i = 1; i <= size; ++i)
    {
        WorkerNode wn("W" + std::to_string(i), i);
        h.insert(wn);
    }

    /**
     * as of now, heap is:
     * [{"W1", 1}, {"W2", 2} ... {"W5", 5}]
     */

    std::map<WorkerNode, int> tracker;
    tracker[h.heap_[3]] = 3;

    for (int i = 0; i < 2; ++i)
    { //decrementing {"W4", 4} twice.
        tracker = h.decr(tracker[h.heap_[3]]);
    }
    WorkerNode key("W4", 2);
    // after two decrements, its index should still be 3.
    BOOST_TEST(tracker[key] == 3);
    // one more decrement should make its index 1.
    tracker = h.decr(tracker[h.heap_[3]]);
    key.numJobs_ = 1;
    BOOST_TEST(tracker[key] == 1);

    /**
     * as of now, heap is:
     * [{"W1", 1}, {"W4", 1}, {"W3", 3}, {"W2", 2}, {"W5", 5}]
     */

    //incrementing {"W1", 1} once.
    tracker = h.incr(0);

    key.workerID_ = "W1";
    key.numJobs_ = 2;
    BOOST_TEST(tracker[key] == 1);
    //incrementing once more, index should be 3.
    tracker = h.incr(tracker[h.heap_[1]]);
    key.numJobs_ = 3;
    BOOST_TEST(tracker[key] == 3);
}

void MinHeap_T::test_case7()
{ // ensuring minHeapify can accurately report multiple index changes.
    MinHeap<WorkerNode> h;
    h.insert(WorkerNode("W1", 1));
    h.insert(WorkerNode("W2", 2));
    h.insert(WorkerNode("W3", 3));
    h.insert(WorkerNode("W0", 3));

    /**
     * heap structure:
     * [{"W1", 1}, {"W2", 2}, {"W3", 3}, {"W0", 3}]
     * 
     * We will manually decrement the last heap element's job count by 2.
     * 
     * expected heap structure following manual decr and minHeapify:
     * [{"W0", 1}, {"W1", 1}, {"W3", 3}, {"W2", 2}]
     */
    h.heap_[h.heap_.size() - 1].numJobs_ -= 2;
    std::map<WorkerNode, int> indices = h.minHeapify(h.heap_.size() - 1);

    WorkerNode key("W0", 1);
    BOOST_TEST(indices[key] == 0);
    key.workerID_ = "W1";
    BOOST_TEST(indices[key] == 1);
    //we don't test "W3", as it's position does not change.
    key.numJobs_ = 2;
    key.workerID_ = "W2";
    BOOST_TEST(indices[key] == 3);
}

test_suite *MinHeap_T::init_test_suite()
{
    test_suite *ts = BOOST_TEST_SUITE("min_heap_test_suite");
    ts->add(BOOST_TEST_CASE(&MinHeap_T::test_case1));
    ts->add(BOOST_TEST_CASE(&MinHeap_T::test_case2));
    ts->add(BOOST_TEST_CASE(&MinHeap_T::test_case3));
    ts->add(BOOST_TEST_CASE(&MinHeap_T::test_case4));
    ts->add(BOOST_TEST_CASE(&MinHeap_T::test_case5));
    ts->add(BOOST_TEST_CASE(&MinHeap_T::test_case6));
    ts->add(BOOST_TEST_CASE(&MinHeap_T::test_case7));
    framework::master_test_suite().add(ts);
    return 0;
}
