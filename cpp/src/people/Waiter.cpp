#include "Waiter.hpp"
#include "GlobalClock.hpp"
#include "Table.hpp"
#include "Job.hpp"
#include "SeatingJob.hpp"
#include "OrderJob.hpp"
#include "Order.hpp"
#include "Party.hpp"
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
#include <memory>
#include <iostream>
#include <boost/algorithm/string.hpp>

Waiter::Waiter(std::string id, GlobalClock &gc, std::vector<std::shared_ptr<Table>> &tables, Foyer &foyer, JobTable &jt, Menu &menu)
    : Worker(gc, jt, menu, id),
      tablespace_(tables),
      foyer_(foyer)
{
    init();
}

void Waiter::handleJob(SeatingJob &sj)
{
    std::cout << getClock() << " " << getId() << ": Handling SJ for Table " << sj.tableID_ << std::endl;
    std::shared_ptr<Party> pPtr = foyer_.removeParty(sj.tableID_);

    Table::WaiterAccess::seatParty(tablespace_[sj.tableID_], pPtr);
    Party::WaiterAccess::setTable(pPtr, tablespace_[sj.tableID_]);
    Party::WaiterAccess::setWaiter(pPtr, shared_from_this());
    Party::WaiterAccess::setMenu(pPtr, std::make_shared<Menu>(menu_));
    Party::WaiterAccess::signalServiceStarted(pPtr);

    std::cout << getClock() << " " << getId() << ": Notified " << pPtr->getPID() << " that service has started.\n";
}

void Waiter::handleJob(OrderJob &oj) //TODO flesh out this handler.
{
    if (oj.order_->getOrderStatus() == OrderStatus::QueuedForSubmission)
    { // for OrderJobs requiring preparation.
        std::cout << getClock() << " " << getId() << ": handling OJ (" << oj.order_->getOrderId() << ")" << std::endl;
        auto tID = oj.order_->getTableID();

        Table::WaiterAccess::notifyParty(tablespace_[tID]); //first, notify Party that their Order has been picked up.

        //then, place job in correct job queue
        //TODO implement OrderStatus to allow conditional handling here.
        //NOTE for now, we'll assume we're passing OJ to Bartender.
        //NOTE for now, we're assuming it's a drink order and we're passing it to B-0.
        std::string bID = "B-0";
        jt_.queueJob(bID, std::make_shared<OrderJob>(oj));
        Order::OrderAccess::setStatus(oj.order_, OrderStatus::QueuedForPrep);
    }
    else // for OrderJobs requiring delivery to Tables (Order is ready)
    {
        Order::OrderAccess::setStatus(oj.order_, OrderStatus::EnRouteForDelivery);
        std::cout << getClock() << " " << getId() << ": picked up completed order " << oj.order_->getOrderId() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));

        Table::WaiterAccess::placeOrder(tablespace_[oj.order_->getTableID()], oj.order_);
        Order::OrderAccess::setStatus(oj.order_, OrderStatus::Delivered);
        std::cout << getClock() << " " << getId() << ": " << oj.order_->getOrderId() << " delivered" << std::endl;
        Table::WaiterAccess::notifyParty(tablespace_[oj.order_->getTableID()]);
    }
}