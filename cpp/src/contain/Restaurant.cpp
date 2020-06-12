#include "Restaurant.hpp"
#include "Waiter.hpp"
#include <vector>
#include <string>
#include <iostream>

Restaurant::Restaurant(unsigned tCount, unsigned wCount, unsigned pCount)
    : tableCount_(tCount),
      waiterCount_(wCount),
      partyCount_(pCount),
      jobTable_(wCount),
      foyer_(tCount),
      door_()
{
}

Restaurant::Restaurant(const Restaurant &r)
    : tableCount_(r.tableCount_),
      waiterCount_(r.waiterCount_),
      partyCount_(r.partyCount_),
      jobTable_(r.jobTable_),
      foyer_(r.foyer_),
      door_(r.door_),
      tables_(r.tables_),
      waiters_(r.waiters_) {}

Restaurant &Restaurant::operator=(const Restaurant &r)
{
    if (this == &r)
        return *this;
    tableCount_ = r.tableCount_;
    waiterCount_ = r.waiterCount_;
    partyCount_ = r.partyCount_;
    jobTable_ = r.jobTable_;
    foyer_ = r.foyer_;
    door_ = r.door_;
    tables_ = r.tables_;
    waiters_ = r.waiters_;
    return *this;
}

void Restaurant::init()
{
    buildTables(); // important that this is done first
    buildWaiters();
}

void Restaurant::buildTables()
{
    std::cout << "building tables...";
    for (int i = 1; i <= tableCount_; ++i)
    {
        tables_.push_back(std::make_shared<Table>(i));
    }
    std::cout << " done.\n";
}

void Restaurant::buildWaiters()
{
    std::cout << "building waiters...";
    for (int i = 1; i <= waiterCount_; ++i)
    {
        waiters_.push_back(std::make_shared<Waiter>("W-" + std::to_string(i), tables_, foyer_, jobTable_));
    }
    std::cout << " done.\n";
}