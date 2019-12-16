#ifndef TABLE_H
#define TABLE_H

#include <vector>

/**
 * Used to seat guests inside of the restaurant 
 * as they dine.
 * */
struct Table
{
    mutable bool isOccupied_;
    const unsigned tableID_;

    //need a party pointer
    //need a vector of guest pointers

    inline constexpr const bool isOccupied() { return isOccupied_; }
    inline constexpr const unsigned tableId() { return tableID_; }
};

#endif // TABLE_H