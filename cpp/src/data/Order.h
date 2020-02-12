#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include "OrderStatus.h"

/**
 * An order. 
 * 
 * Could be further subclassed into FoodOrder 
 * and DrinkOrder, but it really is not necessary,
 * so long as respective methods are called based on
 * the party-waiter messaging protocol.
 * 
 * author: ajm
 * created: 1/29/20
 * last modified: 1/29/20
 **/
class Order
{

public:
    // ctors and copy control
    // should never be used, really.
    Order() : status_(OrderStatus::Defaulted),
              orderId_("DEFAULT_OID"),
              orders_() {}
    // the ctor that should almost always be used
    Order(std::string id, std::vector<int> &orders) : status_(OrderStatus::Initializing),
                                                      orderId_(id),
                                                      orders_(orders) {}
    Order(const Order &) = delete;
    Order &operator=(const Order &) = delete;
    ~Order() {}
    // accessors for const and non-const Orders (mems should always be const)
    inline OrderStatus getStatus() const { return status_; }
    inline const std::string &getOrderId() const { return orderId_; }
    inline const std::string &getOrderId()
    {
        return (static_cast<const Order &>(*this)).getOrderId();
    }
    inline const std::vector<int> &getOrders() const { return orders_; }
    inline const std::vector<int> &getOrders()
    {
        return (static_cast<const Order &>(*this)).getOrders();
    }

private:
    OrderStatus status_;
    const std::string orderId_;
    const std::vector<int> orders_; // a set of menu selections
};

#endif // ORDER_H

/**
 * TODO: write a unit test for Order.
 * TODO: make Order serializable. Can be done using Boost.
 * TODO: how should OrderStatus be updated to maximize encapsulation?
 **/