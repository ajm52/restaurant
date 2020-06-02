#include "Restaurant.h"
#include "Waiter.h"
#include <vector>
#include <string>
#include <iostream>

Restaurant::Restaurant(unsigned tCount, unsigned wCount, unsigned pCount)
    : tableCount_(tCount),
      waiterCount_(wCount),
      partyCount_(pCount),
      jobTable_(wCount),
      foyer_(tCount, jobTable_),
      door_(foyer_)
{
    init();
}

void Restaurant::init()
{
    buildTables(); // important that this is done first
    buildWaiters();
}

void Restaurant::buildTables()
{
    for (int i = 1; i <= tableCount_; ++i)
    {
        Table t(i);
        tables_.push_back(t);
    }
}

void Restaurant::buildWaiters()
{
    for (int i = 1; i <= waiterCount_; ++i)
    {
        Waiter w("W-" + std::to_string(i), tables_, foyer_, jobTable_);
        waiters_.push_back(w);
    }
}