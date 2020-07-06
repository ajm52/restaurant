#include "Bartender.hpp"
#include "OrderJob.hpp"
#include "Order.hpp"
#include <iostream>
#include <future>
#include <chrono>

void Bartender::handleJob(OrderJob &oj)
{
    Order::OrderAccess::setStatus(oj.order_, OrderStatus::ReceivedForPrep);
    std::cout << getClock() << " " << getId() << ": handling OJ for order " << oj.order_->getOrderId() << std::endl;
    auto res = std::async(std::launch::async, [&] {
        //NOTE for now, we will just wait 5 seconds for an order to be prepared.
        //in the future, each dish will be prepared using its prep time.
        std::cout << getClock() << " " << getId() << ": preparing order " << oj.order_->getOrderId() << std::endl;
        Order::OrderAccess::setStatus(oj.order_, OrderStatus::BeingPrepared);
        std::this_thread::sleep_for(std::chrono::seconds(5));
        Order::OrderAccess::setStatus(oj.order_, OrderStatus::ReadyToDeliver);
        std::cout << getClock() << " " << getId() << ": order " << oj.order_->getOrderId() << " is ready for delivery" << std::endl;
        this->queueOrderForDelivery(oj);
    });
}

void Bartender::queueOrderForDelivery(OrderJob &oj)
{
    jt_.queueJob(oj.order_->getWID(), std::make_shared<OrderJob>(oj));
    std::cout << getClock() << " " << getId() << ": order " << oj.order_->getOrderId() << " queued for delivery" << std::endl;
    Order::OrderAccess::setStatus(oj.order_, OrderStatus::QueuedForDelivery);
}