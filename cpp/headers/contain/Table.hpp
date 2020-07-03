#ifndef TABLE_HPP
#define TABLE_HPP

#include "OrderMachine.hpp"
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
     * @param om used by seated Parties to make orders.
     */
    Table(int, OrderMachine &);

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

    /**
     * @description: OM accessor.
     * @returns this table's order machine.
     */
    inline OrderMachine &getOrderMachine() { return om_; }

private:
    mutable bool isOccupied_;
    const unsigned id_;
    OrderMachine &om_;
    std::shared_ptr<Party> party_; ///< null if unoccupied.
    std::shared_ptr<Order> order_;
};

#endif // TABLE_HPP

/**
 * TODO add a mutex and/or boolean flag to ensure thread safety
 * between Parties/Waiters during Order exchanges.
 */