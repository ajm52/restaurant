#include "Restaurant.hpp"
#include "Waiter.hpp"
#include <vector>
#include <string>
#include <iostream>

Restaurant::Restaurant(std::shared_ptr<Menu> menu, unsigned tCount, unsigned wCount, unsigned pCount)
    : tableCount_(tCount),
      waiterCount_(wCount),
      partyCount_(pCount),
      jobTable_(wCount),
      foyer_(tCount),
      door_(),
      tables_(),
      waiters_(),
      doorman_(door_, foyer_, jobTable_),
      menu_(menu) {}

Restaurant::Restaurant(const Restaurant &r)
    : tableCount_(r.tableCount_),
      waiterCount_(r.waiterCount_),
      partyCount_(r.partyCount_),
      jobTable_(r.jobTable_),
      foyer_(r.foyer_),
      door_(r.door_),
      tables_(r.tables_),
      waiters_(r.waiters_),
      doorman_(door_, foyer_, jobTable_),
      menu_(r.menu_) {}

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
    menu_ = r.menu_;
    return *this;
}

Restaurant::~Restaurant()
{
    tables_.clear();
    waiters_.clear();
}

void Restaurant::init()
{
    std::cout << "Restaurant: Building Tables...";
    buildTables();
    std::cout << " done.\nRestaurant: Building Waiters...";
    buildWaiters();
    std::cout << " done.\nRestaurant: Initializing Doorman threads...";
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
        auto wPtr = std::make_shared<Waiter>("W-" + std::to_string(i), tables_, foyer_, jobTable_, menu_);
        waiters_.push_back(wPtr);
    }
}