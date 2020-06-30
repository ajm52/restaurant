#ifndef TABLE_HPP
#define TABLE_HPP

#include <iostream>
#include <vector>
#include <memory>

class Party;
class Order;
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
     * @description: destructor.
     */
    ~Table() = default;

    Table(const Table &) = delete; ///< Table is neither copyable nor movable.
    Table &operator=(const Table &) = delete;
    Table(Table &&) = delete;
    Table &operator=(Table &&) = delete;

    /**
     * @description: occupation status accessor.
     * @returns whether or not this table is occupied.
     */
    inline const bool isOccupied() const { return isOccupied_; }

    /**
     * @description: table ID accessor.
     * @returns the table's id.
     */
    inline const unsigned tableId() const { return id_; }

private:
    mutable bool isOccupied_;      ///< occupation flag.
    const unsigned id_;            ///< a unique table identifier.
    std::shared_ptr<Party> party_; ///< pointer to the Party at this Table (null if unoccupied).
    std::shared_ptr<Order> order_; ///< pointer to the Table's Order.
};

#endif // TABLE_HPP

/**
 * TODO add a mutex and/or boolean flag to ensure thread safety
 * between Parties/Waiters during Order exchanges.
 */