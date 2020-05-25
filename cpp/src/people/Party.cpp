#include "Guest.h"
#include "Door.h"
#include "Restaurant.h"
#include "Party.h"

#include <iostream>
#include <queue>
#include <mutex>

Party::Party(Restaurant &theSpot, const std::vector<Guest const *> &guests, std::string pid)
    : pid_(pid),
      status_(Status::Party::Outside),
      guests_(guests),
      theSpot_(theSpot)
{
    init();
}

Party::Party(Restaurant &theSpot, std::vector<Guest const *> *guests = nullptr, std::string pid)
    : pid_(pid),
      status_(Status::Party::Outside),
      guests_(*guests),
      theSpot_(theSpot)
{
    std::cout << "got here\n";
    init();
}

/**
 * boots up the Party thread.
 **/
void Party::init()
{
    std::cout << "got here\n";
    std::thread t(&Party::run, this);
    std::cout << "and here\n";
    t.join();
}

/**
 * main thread of execution for Party.
 **/
void Party::run()
{
    std::cout << "Hello\n";
}

/**
 * used by parties to enter the restaurant.
 */
void Party::enterRestaurant()
{
    Door *d = theSpot_.getDoor();
    { // Begin critical section
        std::lock_guard<std::mutex> lg(d->getEntryMutex());
        std::queue<Party *> q = d->getEntryQueue();
        q.push(this);
    } // End critical section
    d->signalEntry();
}