#include <iostream>

#include "Restaurant.h"
#include "Guest.h"
#include "Party.h"

Party::Party(Restaurant &theSpot, const std::vector<Guest const *> &guests)
    : status_(Status::Party::Outside),
      guests_(guests),
      theSpot_(theSpot)
{
    init();
}

Party::Party(Restaurant &theSpot, std::vector<Guest const *> *guests)
    : status_(Status::Party::Outside),
      guests_(*guests),
      theSpot_(theSpot)
{
    init();
}

/**
 * boots up the Party thread.
 **/
void Party::init()
{
    std::thread t(&Party::run, this);
    t.join();
}

/**
 * main thread of execution for Party.
 **/
void Party::run()
{
    std::cout << "Hello\n";
}