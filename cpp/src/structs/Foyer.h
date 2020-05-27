#ifndef FOYER_H
#define FOYER_H

#include "Table.h"
#include <boost/signals2.hpp>
#include <memory>
#include <vector>
#include <map>
#include <mutex>

class Party;
class Waiter;

typedef boost::signals2::signal<void(Waiter *, unsigned)> NewPartySignal;

/**
 * @struct <code>Foyer</code>
 * @description: Where parties wait to be seated.
 * @author ajm
 * @created: 2/6/20
 * @modified: 5/26/20
 **/
struct Foyer
{
    /**
     * @description: default constructor.
     */
    Foyer();

    /**
     * @description: called from the Door's EntrySlot
     * to signal a Waiter of a new wait job.
     * @param wid Waiter identifier.
     * @param tid Table identifier.
     */
    void signalWaiter(unsigned, unsigned);

    /**
     * @description: assigns restaurants waiters to this Foyer.
     * @param waiters those being assigned.
     */
    void assignWaiters(std::vector<Waiter *> &);

    /**
     * @description: initializes Foyer-Waiter connections.
     * This is set up so that when a Party is placed in this Foyer,
     * the appropriate Waiter may be notified of their newly assigned
     * job (i.e. waiting the Party).
     */
    void initConnections();

    /**
     * @description: place a party in the foyer.
     * @param id table # where the party should be seated.
     * @param pPtr a pointer to the party to be seated.
     */
    bool putParty(int id, Party *pPtr);

    /**
     * @description: remove and return a party from the foyer.
     * @param id table # for a corresponding party to be seated.
     * @returns a pointer to the corresponding party, or nullptr if 
     * no such mapping exists.
     */
    Party *removeParty(int id);

    std::map<int, Party *> table_;                                 ///< map of <Table #, Party*> pairs
    mutable std::mutex m_;                                         ///< foyer mutex.
    std::vector<std::shared_ptr<NewPartySignal>> newPartySignals_; ///< called when a Party needs seating.
    std::vector<Waiter *> *waiters_;                               ///< the restaurant waiters.
};

#endif // FOYER_H

/**
 * TODO: make Foyer threadsafe with mutex.
 */