#include "Party.hpp"
#include "Menu.hpp"
#include "Guest.hpp"
#include "Door.hpp"
#include "Waiter.hpp"
#include "Table.hpp"
#include "Restaurant.hpp"
#include <iostream>
#include <queue>
#include <mutex>
#include <future>
#include <condition_variable>
#include <memory>
#include <chrono>

void Party::WaiterAccess::signalServiceStarted(std::shared_ptr<Party> p)
{
    p->hasBeenServiced_ = true;
    p->cv_.notify_one();
}

Party::Party(Restaurant &r, unsigned gCount, std::string pid)
    : theRestaurant_(r),
      m_(),
      cv_(),
      pid_(pid),
      guests_(),
      theWaiter_(nullptr),
      theTable_(nullptr),
      theMenu_(nullptr),
      hasBeenServiced_(false) {}

Party::Party(Party &&p)
    : theRestaurant_(p.theRestaurant_),
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
    // restaurant, m, and cv are not reseatable
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
    std::thread t(&Party::run, this);
    mthread_ = std::move(t);
}

void Party::run()
{
    std::cout << this->getPID() << " is awake.\n";
    enterRestaurant();
    awaitService();
    /**
     * 1. after a pause, place an Order on the Table and submit an OrderJob to the JobTable.
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
                theRestaurant_.getDoor().getEntryQueue().push(std::make_shared<Party>(std::move(*this)));
                break;
            }
            catch (const std::exception &e) //TODO clean up this error handling (eventually)
            {
                std::cerr << e.what() << "; trying again in 3 seconds.\n";
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
        }
    } // End critical section

    std::cout << this->getPID() << " entered the restaurant queue.\n";
}

void Party::awaitService()
{
    std::cout << this->getPID() << ": Pinging for service...\n";
    theRestaurant_.getDoor().getCV().notify_one(); // notifies a thread to place this in the Foyer, which notifies a Waiter to place this at a Table.
    std::unique_lock<std::mutex> ul(m_);

    while (checkServiceFlag()) // waits here until notified by their Waiter.
        cv_.wait(ul);

    std::cout << this->getPID() << ": Service notification received.\n"; // at this point, this Party should have access to its Waiter, Table, and Menu.
}

std::shared_ptr<Party> Party::makeParty(Restaurant &r, unsigned gCount, std::string pid)
{
    return std::make_shared<Party>(r, gCount, pid);
}