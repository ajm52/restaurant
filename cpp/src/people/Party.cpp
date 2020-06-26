#include "Party.hpp"
#include "Menu.hpp"
#include "GlobalClock.hpp"
#include "Guest.hpp"
#include "Door.hpp"
#include "Waiter.hpp"
#include "Table.hpp"
#include "Restaurant.hpp"
#include "SimMonitor.hpp"
#include "OrderService.hpp"
#include "Order.hpp"
#include <iostream>
#include <queue>
#include <mutex>
#include <future>
#include <condition_variable>
#include <memory>
#include <chrono>

void Party::WaiterAccess::signalServiceStarted(Party *p)
{
    p->hasBeenServiced_ = true;
    p->cv_.notify_one();
    std::cout << p->getClock() << " " << p->getPID() << ": Waiter notify done.\n";
}

Party::Party(GlobalClock &gc, Restaurant &r, SimMonitor &sm, unsigned gCount, std::string pid)
    : clock_(gc),
      theRestaurant_(r),
      sm_(sm),
      m_(),
      cv_(),
      pid_(pid),
      guests_(),
      theWaiter_(nullptr),
      theTable_(nullptr),
      theMenu_(nullptr),
      hasBeenServiced_(false) {}

Party::Party(Party &&p)
    : clock_(p.clock_),
      theRestaurant_(p.theRestaurant_),
      sm_(p.sm_),
      m_(),
      cv_(),
      mthread_(std::move(p.mthread_)),
      pid_(p.pid_),
      guests_(std::move(p.guests_)),
      theWaiter_(p.theWaiter_),
      theTable_(p.theTable_),
      theMenu_(p.theMenu_),
      hasBeenServiced_(p.hasBeenServiced_)
{
    p.theWaiter_ = nullptr;
    p.theTable_ = nullptr;
    p.theMenu_ = nullptr;
}

Party &Party::operator=(Party &&p)
{
    if (this == &p)
        return *this;
    // restaurant, clock, sm, m, and cv are not reseatable
    mthread_ = std::move(p.mthread_);
    pid_ = p.pid_;
    guests_ = std::move(p.guests_);
    theWaiter_ = std::move(p.theWaiter_);
    theTable_ = std::move(p.theTable_);
    theMenu_ = std::move(p.theMenu_);
    hasBeenServiced_ = p.hasBeenServiced_;
    return *this;
}

void Party::init()
{
    std::thread t(&Party::run, std::ref(*this));
    mthread_ = std::move(t);
}

void Party::run()
{
    std::cout << getClock() << " " << getPID() << " is awake.\n";

    enterRestaurant();

    awaitService();

    std::this_thread::sleep_for(std::chrono::seconds(2));
    // ... Wait some time, make an order, and submit.
    Order o = createOrder(1, 'F'); //NOTE 1 and 'F' are magic constants! Short for "1 food selection"
    submitOrder(o);

    // wait for a notification from Waiter that it's received the Order.

    // wait again for the Order to arrive.

    /**
     * 2. wait until Waiter notifies that it has picked up the Order.
     * 3. wait again until the Waiter notifies that the Order has been placed on the Table.
     * 4. run a Timer. 
     * 5. Leave the Table, and exit the restaurant. 
     */
}

void Party::enterRestaurant()
{
    { // Begin critical section
        while (true)
        {
            try
            {
                std::lock_guard<std::mutex> lg(theRestaurant_.getDoor().getEntryMutex());
                theRestaurant_.getDoor().getEntryQueue().push(this);
                break;
            }
            catch (const std::exception &e) //TODO clean up this error handling (eventually)
            {
                std::cerr << e.what() << "; trying again in 3 seconds.\n";
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
        }
    } // End critical section

    std::cout << getPID() << " entered the restaurant queue.\n";
}

void Party::awaitService()
{
    std::cout << getClock() << " " << getPID() << ": Pinging for service...\n";
    theRestaurant_.getDoor().getCV().notify_one(); // notifies a thread to place this in the Foyer, which notifies a Waiter to place this at a Table.
    std::unique_lock<std::mutex> ul(m_);

    while (!checkServiceFlag())
    { // waits here until notified by their Waiter.
        std::cout << getClock() << " " << getPID() << ": Waiting for notification from a Waiter..\n";
        cv_.wait(ul);
    }

    std::cout << getClock() << " " << getPID() << ": Service notification received.\n"; // at this point, this Party should have access to its Waiter, Table, and Menu.
}

Order Party::createOrder(unsigned count, char type) //TODO move this method into OrderService.
{
    if (!theTable_ || !theMenu_)
        return Order();

    std::vector<std::string> selections(count);
    for (auto i = 0; i < count; ++i)
    {
        selections.push_back(theMenu_->selectOption(type));
    }
    std::string orderID = sm_.getNextOrderID();
    Order o(orderID, selections, theTable_->tableId());
    return o;
}

void Party::submitOrder(Order o)
{
    std::cout << getClock() << " " << getPID() << ": Submitting Order " << o.getOrderId() << ".\n";
    OrderService::forwardOrder(o, theWaiter_);
    std::cout << getClock() << " " << getPID() << ": " << o.getOrderId() << " submitted.\n";
}

std::shared_ptr<Party> Party::makeParty(GlobalClock &gc, Restaurant &r, SimMonitor &sm, unsigned gCount, std::string pid)
{
    return std::make_shared<Party>(gc, r, sm, gCount, pid);
}