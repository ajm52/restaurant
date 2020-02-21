#define BOOST_TEST_MODULE MinHeap_Test

#include <boost/test/included/unit_test.hpp>
#include "MinHeap.cpp"

/**
 * Unit test for MinHeap.
 * author ajm
 * created: 2/21/20
 * modified: 2/21/20
 */

BOOST_AUTO_TEST_SUITE(minheap_test_suite)

BOOST_AUTO_TEST_CASE(case1)
{ // empty heap
    MinHeap h;
    BOOST_CHECK(&h);
    BOOST_TEST(h.heap_.size() == 0);
}

BOOST_AUTO_TEST_CASE(case2)
{ // heap of size 1
    MinHeap h;
    int size = 1, value = 1;
    BOOST_CHECK(&h);
    h.insert(value);
    BOOST_TEST(h.heap_.size() == size);
    BOOST_TEST(h.heap_[0] == value);
}

BOOST_AUTO_TEST_CASE(case3)
{ // heap of size 5
    MinHeap h;
    int size = 5;
    BOOST_CHECK(&h);
    for (int i = size; i > 0; --i)
    {
        h.insert(i);
    }
    BOOST_TEST(h.heap_.size() == 5);
    /**
     * following the previous order of inserts,
     * heap_ should be [1, 2, 4, 5, 3].
     * If you don't believe me, check it yourself.
     */
    int *testArray = new int[5];
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

BOOST_AUTO_TEST_SUITE_END()