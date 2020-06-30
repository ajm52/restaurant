#include "Restaurant.hpp"
#include "GlobalClock.hpp"
#include "Waiter.hpp"
#include <vector>
#include <string>
#include <iostream>

Restaurant::Restaurant(GlobalClock &clock, Menu &menu, unsigned tCount, unsigned wCount, unsigned pCount)
    : clock_(clock),
      tableCount_(tCount),
      waiterCount_(wCount),
      partyCount_(pCount),
      jobTable_(wCount),
      foyer_(),
      door_(),
      menu_(menu),
      tables_(),
      waiters_(),
      doorman_(door_, foyer_, jobTable_, clock_) {}

void Restaurant::init()
{
    std::cout << getClock() << " Restaurant: Building Tables...";
    buildTables();
    std::cout << " done.\n"
              << getClock() << " Restaurant: Building Waiters...";
    buildWaiters();
    std::cout << " done.\n"
              << getClock() << " Restaurant: Initializing Doorman threads...";
    doorman_.init();
    std::cout << " done.\n";
}

void Restaurant::buildTables()
{
    for (int i = 0; i < tableCount_; ++i)
    {
        tables_.push_back(std::make_shared<Table>(i));
    }
}

void Restaurant::buildWaiters()
{
    for (int i = 0; i < waiterCount_; ++i)
    {
        auto wPtr = std::make_shared<Waiter>("W-" + std::to_string(i), clock_, tables_, foyer_, jobTable_, menu_);
        waiters_.push_back(wPtr);
    }
}