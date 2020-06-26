#include "Bartender.hpp"
#include "OrderJob.hpp"
#include <iostream>

Bartender::Bartender(Bartender &&b)
    : Worker(std::move(b)) {}

Bartender &Bartender::operator=(Bartender &&b)
{
    Worker::operator=(std::move(b));
    return *this;
}

const int Bartender::getIDNumber() const
{
    int base = Worker::getIDNumber();
    return base == -1 ? base : base + jt_.waiterCount() + jt_.cookCount();
}

void Bartender::handleJob(OrderJob &oj)
{
    std::cout << getClock() << " " << getId() << ": handling OJ for order " << oj.order_.getOrderId() << std::endl;
}