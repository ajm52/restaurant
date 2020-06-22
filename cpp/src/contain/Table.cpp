#include "Table.hpp"
#include "Party.hpp"
#include <memory>

Table::Table(int id)
    : isOccupied_(false),
      id_(id),
      party_(nullptr) {}

bool Table::WaiterAccess::seatParty(std::shared_ptr<Table> t, Party *p)
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