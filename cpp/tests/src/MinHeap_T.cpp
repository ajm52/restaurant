#define BOOST_TEST_MODULE MinHeap_Test

#include <boost/test/included/unit_test.hpp>
#include "MinHeap.cpp"
#include "WorkerNode.h"
#include <ostream>

/**
 * Unit test for MinHeap.
 * author ajm
 * created: 2/21/20
 * modified: 2/24/20
 */

BOOST_AUTO_TEST_SUITE(minheap_test_suite)

BOOST_AUTO_TEST_CASE(case1)
{ // empty heap
    MinHeap<int> h;
    BOOST_CHECK(&h);
    BOOST_TEST(h.heap_.size() == 0);
}

BOOST_AUTO_TEST_CASE(case2)
{ // heap<int> of size 1
    MinHeap<int> h;
    int size = 1, value = 1;
    BOOST_CHECK(&h);
    h.insert(value);
    BOOST_TEST(h.heap_.size() == size);
    BOOST_TEST(h.heap_[0] == value);
}

BOOST_AUTO_TEST_CASE(case3)
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

BOOST_AUTO_TEST_CASE(case4)
{ // testing decr(int) w/ Heap<int> of size 3
    MinHeap<int> h;
    int size = 3;
    for (int i = 0; i < size; ++i)
    { // inserting 1, 3, 5.
        h.insert(2 * i + 1);
    }
    int index = 1;
    for (int i = 0; i < size; ++i)
    { // decrementing 3, 3 times.
        index = h.decr(index);
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

BOOST_AUTO_TEST_CASE(case5)
{ // testing incr(int) w/ Heap<int> of size 3
    MinHeap<int> h;
    int size = 3;
    for (int i = 0; i < size; ++i)
    { // inserting 1, 3, 5.
        h.insert(2 * i + 1);
    }
    int index = 0;
    for (int i = 0; i < size; ++i)
    { // incrementing 1, 3 times.
        index = h.incr(index);
    }
    //h should now be [3, 4, 5]
    int *testArray = new int[size];
    testArray[0] = 3;
    testArray[1] = 4;
    testArray[2] = 5;
    for (int i = 0; i < size; ++i)
        BOOST_TEST(testArray[i] == h.heap_[i]);

    delete[] testArray;
    std::cout << "done 5" << std::endl;
}

BOOST_AUTO_TEST_CASE(case6)
{ // testing incr(int) and decr(int) w/ Heap<WorkerNode> of size 5.
    MinHeap<WorkerNode> h;
    int size = 5;
    for (int i = 1; i <= size; ++i)
    {
        WorkerNode wn("W" + std::to_string(i), i);
        int ind = h.insert(wn);
    }

    /**
     * as of now, heap is:
     * [{"W1", 1}, {"W2", 2} ... {"W5", 5}]
     */
    int index = 3;
    for (int i = 0; i < 2; ++i)
    { //decrementing {"W4", 4} twice.
        index = h.decr(index);
    }
    // after two decrements, its index should still be 3.
    BOOST_TEST(index == 3);
    // one more decrement should make its index 1.
    index = h.decr(index);
    BOOST_TEST(index == 1);

    /**
     * as of now, heap is:
     * [{"W1", 1}, {"W4", 1}, {"W3", 3}, {"W2", 2}, {"W5", 5}]
     */
    int indexTwo = 0;
    //incrementing {"W1", 1} once.
    indexTwo = h.incr(indexTwo);
    BOOST_TEST(indexTwo == 1);
    //incrementing once more, indexTwo should be 3.
    indexTwo = h.incr(indexTwo);
    BOOST_TEST(indexTwo == 3);
}

BOOST_AUTO_TEST_SUITE_END()