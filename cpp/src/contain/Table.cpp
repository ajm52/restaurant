#include "Table.h"

Table::Table(int id) : id_(id)
{
}

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