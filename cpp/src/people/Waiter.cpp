#include "Waiter.hpp"
#include "GlobalClock.hpp"
#include "Table.hpp"
#include "Job.hpp"
#include "SeatingJob.hpp"
#include "OrderJob.hpp"
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
    std::cout << getClock() << " " << getId() << ": handling OJ for order " << oj.order_->getOrderId() << std::endl;
}