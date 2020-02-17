#ifndef ORDER_H
#define ORDER_H

#include "OrderStatus.h"

#include <string>
#include <vector>

/**
 * @class Order
 * @description: Represents a set of either drink or food orders from a given table.
 * @author ajm
 * @created: 1/29/20
 * @modified: 2/17/20
 **/
class Order
{
public:
    /**
     * @description: <code>Order</code> default constructor, mainly for debugging.
     * Data members are defaulted initialized.
     **/
    Order() : status_(OrderStatus::Defaulted),
              orderId_("DEFAULT_OID"),
              orders_() {}

    /**
     * @description: <code>Order</code> go-to constructor.
     * @param id order id string.
     * @param orders attached orders.
     **/
    Order(std::string id, std::vector<int> &orders) : status_(OrderStatus::Initializing),
                                                      orderId_(id),
                                                      orders_(orders) {}

    /**
     * @description: <code>Order</code> copy constructor.
     * @param order what <code>this</code> copies from.
     */
    Order(const Order &);

    /**
     * @description: <code>Order</code> copy assignment operator.
     * @param order what <code>this</code> copies from.
     */
    Order &operator=(const Order &);

    /**
     * @description: <code>Order</code> destructor.
     */
    ~Order() {}

    /**
     * @description: accessor for <code>this Order</code>'s status.
     * @returns a copy of <code>this Order</code>'s status.
     */
    inline OrderStatus getStatus() const { return status_; }

    /**
     * @description: accessor for <code>this Order</code>'s id string.
     * @returns a const reference to <code>this Order</code>'s id string.
     */
    inline const std::string &getOrderId() const { return orderId_; }

    /**
     * @description: accessor for <code>this Order</code>'s order set.
     * @returns a const reference to <code>this Order</code>'s order set.
     */
    inline const std::vector<int> &getOrders() const { return orders_; }

private:
    OrderStatus status_;      ///< Status, to be displayed by front-end.
    std::string orderId_;     ///< id string, unique to each order.
    std::vector<int> orders_; ///< menu selections.
};

#endif // ORDER_H

/**
 * TODO: write a unit test for Order.
 * TODO: make Order serializable. Can be done using Boost.
 * TODO: how should OrderStatus be updated to maximize encapsulation?
 **/