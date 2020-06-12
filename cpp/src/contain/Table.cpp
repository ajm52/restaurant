#include "Table.hpp"
#include "Party.hpp"

Table::Table(int id)
    : isOccupied_(false),
      id_(id),
      party_(nullptr) {}

bool Table::WaiterAccess::setParty(Table *t, Party *p)
{
    if (!t->isOccupied_)
    {
        t->party_ = p;
        t->isOccupied_ = true;
        std::cout << "PartyID#" << p->getPID() << " has been seated at Table#"
                  << t->id_ << ".\n";
        return true;
    }
    else
    {
        std::cout << "Error in seating PartyID#" << p->getPID() << ": Table# "
                  << "is already occupied!\n";
        return false;
    }
}