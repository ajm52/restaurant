#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include "Status.h"

/**
 * Used to seat restaurant guests.
 * 
 * author: ajm
 * created: 1/28/20
 * last modified: 1/28/20
 **/
class Table
{
    mutable bool isOccupied_;
    const unsigned id_;

    //need a party pointer

    inline constexpr const bool isOccupied() { return isOccupied_; }
    inline constexpr const unsigned tableId() { return id_; }
};

#endif // TABLE_H