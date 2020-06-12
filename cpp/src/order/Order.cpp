#include "Order.hpp"

Order::Order(const Order &order) : orderId_(order.orderId_), orders_(order.orders_) {}

Order &Order::operator=(const Order &order)
{
    if (this == &order)
        return *this;
    this->orderId_ = order.orderId_;
    this->orders_ = order.orders_;
    return *this;
}