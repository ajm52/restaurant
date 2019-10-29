#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>

/*
Used to seat guests.
*/
class table
{
private:
    unsigned int cap_; //guest capacity
    unsigned int id_;  //table id

    std::vector<std::string> guests_; //identified by id

    bool isTaken_;

public:
    explicit table::table();
    explicit table::table(unsigned int cap = 4);
    const unsigned int const table::getCap();
    const bool const table::isTaken();
    const std::vector<std::string> &const table::getGuests();
    const bool table::seatGuests(const std::vector<std::string> &guests);
    void table::clearGuests();
};

#endif // TABLE_H