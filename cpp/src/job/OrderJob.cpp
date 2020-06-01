#include "OrderJob.h"
#include "Waiter.h"
#include <iostream>

void OrderJob::handleJob(Waiter &w)
{
    std::cout << w.getId() << " has begun OrderJob " << this->order_.getOrderId() << std::endl;
}