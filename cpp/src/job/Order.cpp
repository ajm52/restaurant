#include "Order.hpp"

Order::Order(const Order &order)
    : orderId_(order.orderId_),
      selections_(order.selections_),
      tableID_(order.tableID_) {}

Order &Order::operator=(const Order &order)
{
    if (this == &order)
        return *this;
    this->orderId_ = order.orderId_;
    this->selections_ = order.selections_;
    this->tableID_ = order.tableID_;
    return *this;
}