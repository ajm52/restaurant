#define BOOST_TEST_MODULE Queue_Test

#include <boost/test/included/unit_test.hpp>
#include "Queue.cpp"

/**
 * Unit test for Queue.
 * author: ajm
 * created: 2/21/20
 * modified: 2/21/20
 */

BOOST_AUTO_TEST_SUITE(queue_test_suite)

BOOST_AUTO_TEST_CASE(case1)
{ // empty queue
    Queue q;
    BOOST_CHECK(&q);
    BOOST_TEST(q.size_ == 0);
    BOOST_TEST(q.tail_->value_ == -1);
    BOOST_TEST(q.head_ == nullptr);
}

BOOST_AUTO_TEST_CASE(case2)
{ // q of size 1.
    Queue q;
    int value = 0;
    q.enqueue(value);
    BOOST_CHECK(&q);
    BOOST_TEST(q.size_ == 1);
    BOOST_TEST(q.head_->value_ == value);
    BOOST_TEST(q.head_->prev_ == q.tail_);
    BOOST_TEST(q.tail_->next_ == q.head_);
}

BOOST_AUTO_TEST_CASE(case3)
{ // q of size 5.
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

BOOST_AUTO_TEST_SUITE_END()