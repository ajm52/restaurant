#define BOOST_TEST_DYN_LINK

#include "Queue_T.h"
#include "Queue.cpp"
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

/**
 * Unit test for Queue.
 * author: ajm
 * created: 2/21/20
 * modified: 3/2/20
 */

void Queue_T::test_case1()
{ // empty queue
    Queue q;
    BOOST_CHECK(&q);
    BOOST_TEST(q.size_ == 0);
    BOOST_TEST(q.tail_->value_ == -1);
    BOOST_TEST(q.head_ == nullptr);
}

void Queue_T::test_case2()
{ // q of size 1
    Queue q;
    int value = 0;
    q.enqueue(value);
    BOOST_CHECK(&q);
    BOOST_TEST(q.size_ == 1);
    BOOST_TEST(q.head_->value_ == value);
    BOOST_TEST(q.head_->prev_ == q.tail_);
    BOOST_TEST(q.tail_->next_ == q.head_);
}

void Queue_T::test_case3()
{ // q of size 5
    Queue q;
    int size = 5;
    for (int i = 0; i < size; ++i)
        q.enqueue(i);
    BOOST_CHECK(&q);
    BOOST_TEST(q.size_ == size);

    Node *current = q.head_;
    Node *prev = current->prev_;
    for (int i = 0; i < size; ++i)
    {
        BOOST_TEST(current->value_ == i);
        Node *toCheckNext = prev->prev_;
        current = prev;
        prev = toCheckNext;
    }
    BOOST_TEST(current == q.tail_);
}

test_suite *Queue_T::init_test_suite()
{
    test_suite *ts = BOOST_TEST_SUITE("queue_test_suite");
    ts->add(BOOST_TEST_CASE(&Queue_T::test_case1));
    ts->add(BOOST_TEST_CASE(&Queue_T::test_case2));
    ts->add(BOOST_TEST_CASE(&Queue_T::test_case3));
    framework::master_test_suite().add(ts);
    return 0;
}
