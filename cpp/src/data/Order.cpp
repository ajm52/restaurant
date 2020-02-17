#include "Order.h"

Order::Order(const Order &order) : status_(order.status_), orderId_(order.orderId_), orders_(order.orders_) {}

Order &Order::operator=(const Order &order)
{
    if (this == &order)
        return *this;
    this->status_ = order.status_;
    this->orderId_ = order.orderId_;
    this->orders_ = order.orders_;
    return *this;
}