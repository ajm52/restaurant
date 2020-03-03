#define BOOST_TEST_DYN_LINK

#include "Order_T.h"
#include "OrderStatus.h"
#include "Order.h"
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

/**
 * Unit test for Order.h
 * author: ajm
 * created: 2/3/20
 * last modified: 3/2/20
 **/
std::vector<int> selections{1, 2, 3, 4};

void Order_T::test_case1()
{ //Order using zero arg ctor
    Order o;
    BOOST_CHECK(&o);
    BOOST_TEST(o.getOrderId() == "DEFAULT_OID");
    BOOST_TEST(o.getStatus() == OrderStatus::Defaulted);
    BOOST_TEST(o.getOrders().size() == 0);
}

void Order_T::test_case2()
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

test_suite *Order_T::init_test_suite()
{
    test_suite *ts = BOOST_TEST_SUITE("order_test_suite");
    ts->add(BOOST_TEST_CASE(&Order_T::test_case1));
    ts->add(BOOST_TEST_CASE(&Order_T::test_case2));
    framework::master_test_suite().add(ts);
    return 0;
}
