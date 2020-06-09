#ifndef TABLE_HPP
#define TABLE_HPP

#include "Status.hpp"
#include <iostream>
#include <vector>

class Party;
class Waiter;

/**
 * Used to seat restaurant guests.
 * 
 * author: ajm
 * created: 1/28/20
 * last modified: 5/26/20
 **/
class Table
{
public:
    /**
     * @class WaiterAccess
     * @description: Allows Waiters to seat Parties.
     * @author ajm
     * @created: 5/26/20
     * @modified: 5/26/20
     */
    class WaiterAccess
    {
        static bool setParty(Table *, Party *);
        friend class Waiter;
    };

    /**
     * Table constructor.
     */
    Table(int);

    /**
     * occupation status accessor.
     */
    inline constexpr const bool isOccupied() { return isOccupied_; }

    /**
     * table ID accessor.
     */
    inline constexpr const unsigned tableId() { return id_; }

private:
    mutable bool isOccupied_; ///< occupation flag.
    const unsigned id_;       ///< a unique table identifier.
    Party *party_;            ///< pointer to the Party at this Table (null if unoccupied).
};

#endif // TABLE_HPP