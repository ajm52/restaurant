#include "Party.h"
#include "Menu.h"
#include "Guest.h"
#include "Door.h"
#include "Waiter.h"
#include "Table.h"
#include "Restaurant.h"
#include <iostream>
#include <queue>
#include <mutex>
#include <future>

Party::Party(Restaurant &theSpot, const std::vector<Guest const *> &guests, std::string pid)
    : pid_(pid),
      status_(Status::Party::Outside),
      guests_(guests),
      theSpot_(theSpot)
{
    init();
}

Party::Party(Restaurant *theSpot, std::vector<Guest const *> *guests = nullptr, std::string pid)
    : pid_(pid),
      status_(Status::Party::Outside),
      guests_(*guests),
      theSpot_(*theSpot)
{
    init();
}

void Party::init()
{
    std::thread t(&Party::run, this);
    t.join();
}

void Party::run()
{
    std::cout << "Party#" << this->getPID() << " says hello.\n";
    enterRestaurant();
    Waiter *theWaiter;

    std::future<Table *> theTable;
}

void Party::enterRestaurant()
{
    Door *d = theSpot_.getDoor();
    { // Begin critical section
        std::lock_guard<std::mutex> lg(d->getEntryMutex());
        std::queue<Party *> q = d->getEntryQueue();
        q.push(this);
    } // End critical section
}

Waiter *Party::awaitService()
{
}