#include "OrderMachine.hpp"
#include "Order.hpp"
#include "OrderJob.hpp"
#include "Waiter.hpp"
#include "Party.hpp"
#include <memory>
#include <string>
#include <vector>
#include <mutex>

void OrderMachine::submitOrder(const std::shared_ptr<std::vector<std::string>> selections, const std::shared_ptr<Party> p)
{
    std::shared_ptr<Order> o;
    std::string wid = "W-0"; //NOTE we assume a single waiter for now.

    { //begin critical
        std::lock_guard<std::mutex> lg(m_);
        o = std::make_shared<Order>(getNextOrderID(), wid, selections, p->getTable()->tableId());
        incrOrderCount();
    } //end critical

    auto jPtr = std::make_shared<OrderJob>(o);
    auto wID = p->getWaiter()->getId();
    jt_.queueJob(wID, jPtr); //JobTable is internally sync'd, so no need to sync here.
    Order::OrderAccess::setStatus(o, OrderStatus::QueuedForSubmission);
}