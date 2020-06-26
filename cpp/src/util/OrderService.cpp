#include "OrderService.hpp"
#include "Order.hpp"
#include "OrderJob.hpp"
#include "Waiter.hpp"
#include <memory>

void OrderService::forwardOrder(Order o, std::shared_ptr<Waiter> w)
{
    auto pOj = std::make_shared<OrderJob>(o);
    auto wID = w->getIDNumber();
    w->getJobTable().queueJob(wID, pOj);
    w->getJobTable().getCV(wID)->notify_one();
}