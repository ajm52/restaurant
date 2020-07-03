#include "Table.hpp"
#include "Party.hpp"
#include "OrderMachine.hpp"
#include <memory>

Table::Table(int id, OrderMachine &om)
    : isOccupied_(false),
      id_(id),
      om_(om),
      party_(),
      order_() {}

bool Table::WaiterAccess::seatParty(std::shared_ptr<Table> t, std::shared_ptr<Party> p)
{
    if (!t->isOccupied_)
    {
        t->party_ = p;
        t->isOccupied_ = true;
        return true;
    }
    else
    {
        return false;
    }
}