#include "Bartender.hpp"
#include "OrderJob.hpp"
#include <iostream>

void Bartender::handleJob(OrderJob &oj)
{
    std::cout << getClock() << " " << getId() << ": handling OJ for order " << oj.order_->getOrderId() << std::endl;
}