#include "Table.hpp"
#include "Party.hpp"
#include <memory>

Table::Table(int id)
    : isOccupied_(false),
      id_(id),
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