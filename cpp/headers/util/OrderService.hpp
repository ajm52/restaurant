#ifndef ORDERSERVICE_HPP
#define ORDERSERVICE_HPP

#include "Order.hpp"

class Waiter;
class Party;

/**
 * @class OrderService
 * @author ajm
 * @description: A collection of static helper methods pertaining to 
 * getting Orders submitted.
 */
class OrderService
{
private:
    /**
     * @description: forwards an Order to the assigned Waiter.
     * @param o the order being forwarded.
     * @param w the waiter receiving the order.
     */
    static void forwardOrder(Order, std::shared_ptr<Waiter>);
    friend class Party;
};
#endif // ORDERSERVICE_HPP

/**
 * TODO write static accessor methods that allow Waiters 
 * to pass Orders to the Kitchen/Bar.
 */