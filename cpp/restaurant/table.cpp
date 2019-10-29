#include "table.h"
/*
table.cpp implementation
created 10/29/19 by ajm
*/

table::table() : cap_(4), isTaken_(false), guests_(cap_, 0) {}

table::table(unsigned int cap = 4) : cap_(cap), isTaken_(false), guests_(cap_, 0) {}

const unsigned int const table::getCap() { return cap_; }

const bool const table::isTaken() { return isTaken_; }

const std::vector<std::string> &const table::getGuests() { return guests_; }

const bool table::seatGuests(const std::vector<std::string> &guests)
{
    if (isTaken_ || guests_.size() != 0)
        return false;
    //claim the table
    isTaken_ = true;
    for (std::vector<std::string>::const_iterator itr = guests.begin(); itr != guests.end(); ++itr)
    {
        guests_.push_back(*itr);
    }
    return true;
}

void table::clearGuests()
{
    if (!isTaken_)
        return;
    guests_.clear();
    isTaken_ = false;
}