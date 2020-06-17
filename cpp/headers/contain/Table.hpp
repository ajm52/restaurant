#ifndef TABLE_HPP
#define TABLE_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <optional>

class Party;
class Waiter;

/**
 * @class Table
 * @description: Used to seat restaurant guests.
 * @author ajm
 **/
class Table
{
public:
    /**
     * @class WaiterAccess
     * @description: Allows Waiters to seat Parties.
     * @author ajm
     */
    class WaiterAccess
    {
        /**
         * @description: allows Waiters to seat Parties at Tables.
         * @param t target table.
         * @param p to be seated.
         */
        static bool seatParty(std::shared_ptr<Table>, std::shared_ptr<Party>);
        friend class Waiter;
    };

    /**
     * @description: constructor.
     * @param id table id.
     */
    Table(int);

    /**
     * @description: occupation status accessor.
     * @returns whether or not this table is occupied.
     */
    inline constexpr const bool isOccupied() { return isOccupied_; }

    /**
     * @description: table ID accessor.
     * @returns the table's id.
     */
    inline constexpr const unsigned tableId() { return id_; }

private:
    mutable bool isOccupied_;                     ///< occupation flag.
    const unsigned id_;                           ///< a unique table identifier.
    std::optional<std::shared_ptr<Party>> party_; ///< pointer to the Party at this Table (null if unoccupied).
};

#endif // TABLE_HPP