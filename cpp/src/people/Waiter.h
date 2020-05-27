#ifndef WAITER_H
#define WAITER_H

#include "Person.h"
#include "Worker.h"
#include "Table.h"
#include "Foyer.h"
#include "Multiplexer.h"
#include <boost/signals2.hpp>
#include <vector>

/**
* @struct IncomingPartySlot
* @description: callback used by Foyer to assign a waiting job to this Waiter.
* @author ajm
* @created: 5/26/20
* @modified: 5/26/20
**/
struct IncomingPartySlot
{
    /**
     * @description: callback for new waiting job assignment.
     * notifies this Waiter that a Party is waiting to be seated
     * in the Foyer.
     * @param w the assigned Waiter.
     * @param tID table where the Party shall be seated.
     */
    void operator()(Waiter *, unsigned);
};

/**
 * @class <code>Waiter</code>
 * @description: A restaurant waiter. Inherits from <code>Worker</code>.
 * @author ajm
 * @created: 2/19/20
 * @modified: 5/26/20
 */
class Waiter : public Worker
{
public:
    /**
     * @description: constructor.
     * @param id waiter id string.
     * @param fd waiter fd.
     * @param tables the tablespace.
     * @param foyer the foyer.
     */
    Waiter(std::string, int, std::vector<Table> &, Foyer &);

    /**
     * @description: Registers waiter's main FD in Multiplexer.
     * @returns true on success, false otherwise.
     */
    bool registerMainFD();

    /**
     * @description: Registers a party FD in Multiplexer.
     * @param fd party fd to register.
     * @returns true on success, false otherwise.
     */
    bool registerPartyFD(int);

    /**
     * @description: Used to seat Parties.
     * @param tID id of the Table where the Party shall be seated.
     * @param p Party to be seated.
     */
    void seatParty(unsigned, Party *);

    /**
     * @description: Accessor for foyer.
     */
    inline Foyer &getFoyer() { return foyer_; }

    /**
     * @description: Accessor for tablespace.
     */
    inline std::vector<Table> &getTablespace() { return tablespace_; }

    /**
     * @description: Accessor for slot.
     */
    inline IncomingPartySlot &getSlot() { return slot_; }

private:
    Multiplexer selector_;           ///< I/O multiplexer.
    std::vector<Table> &tablespace_; ///< where parties are seated.
    Foyer &foyer_;                   ///< where Parties wait to be seated.
    IncomingPartySlot slot_;         ///< called when a Party requires seating.
};

/**
 * waiter read FDs:
 * [0] -> main FD (will be written to by the entry Door hook)
 * 
 * [1] -> kitchen FD (will be written to by Cooks)
 * 
 * [2] -> bar FD (will be written to by Bartenders)
 * 
 * [3...] -> written to and from by Parties that come and go.
 * when a Party leaves, its FD must be removed.
 * 
 * When a waiter is assigned a new Party, it takes the FD from
 * Foyer, registers it as a read socket in its Multiplexer, and
 * writes a Greeting.
 * 
 * TODO: 
 * - add private member pointer to Foyer.
 * - add access to Tables.
 * 
 * LATER:
 * - add access to Kitchen.
 * - add access to Bar.
 */
#endif // WAITER_H