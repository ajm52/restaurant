#define BOOST_TEST_MODULE Order_Test
#include <boost/test/included/unit_test.hpp>
#include "Order.h"
#include "OrderStatus.h"

/**
 * Unit test for Order.h
 * author: ajm
 * created: 2/3/20
 * last modified: 2/3/20
 **/

BOOST_AUTO_TEST_SUITE(order_test_suite)

std::vector<int> selections{1, 2, 3, 4};

BOOST_AUTO_TEST_CASE(case1)
{ //Order using zero arg ctor
    Order o;
    BOOST_CHECK(&o);
    BOOST_TEST(o.getOrderId() == "DEFAULT_OID");
    BOOST_TEST(o.getStatus() == OrderStatus::Defaulted);
    BOOST_TEST(o.getOrders().size() == 0);
}

BOOST_AUTO_TEST_CASE(case2)
{ //Order using standard ctor
    Order o("Some order", selections);
    BOOST_CHECK(&o);
    BOOST_TEST(o.getOrderId() == "Some order");
    BOOST_TEST(o.getStatus() == OrderStatus::Initializing);
    BOOST_TEST(o.getOrders().size() == 4);
    for (auto i = 0; i < o.getOrders().size(); ++i)
    {
        BOOST_TEST(o.getOrders()[i] == selections[i]);
    }
}

BOOST_AUTO_TEST_CASE(case3)
{ //testing const accessors
    //NOTE: How to catch potential compile time errors?
    const Order o("Some order", selections);
    BOOST_TEST(o.getOrderId() == "Some order");
    BOOST_TEST(o.getStatus() == OrderStatus::Initializing);
}

BOOST_AUTO_TEST_CASE(case4)
{ //uncopyable test
    BOOST_TEST(std::is_copy_constructible<Order>::value == 0);
    BOOST_TEST(std::is_copy_assignable<Order>::value == 0);
}

BOOST_AUTO_TEST_SUITE_END()