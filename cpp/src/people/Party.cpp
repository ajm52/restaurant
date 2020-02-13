#include "Guest.h"
#include "Restaurant.h"
#include "Party.h"

#include <iostream>

Party::Party(Restaurant &theSpot, const std::vector<Guest const *> &guests)
    : status_(Status::Party::Outside),
      guests_(guests),
      theSpot_(theSpot)
{
    init();
}

Party::Party(Restaurant &theSpot, std::vector<Guest const *> *guests = nullptr)
    : status_(Status::Party::Outside),
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