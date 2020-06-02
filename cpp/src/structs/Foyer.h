#ifndef FOYER_H
#define FOYER_H

#include "Table.h"
#include "Waiter.h"
#include "JobTable.h"
#include <boost/signals2.hpp>
#include <memory>
#include <vector>
#include <queue>
#include <map>
#include <mutex>

class Party;

/**
 * @struct <code>Foyer</code>
 * @description: Where parties wait to be seated.
 * @author ajm
 * @created: 2/6/20
 * @modified: 6/2/20
 **/
struct Foyer
{
    /**
     * @description: default constructor.
     */
    Foyer();

    /**
     * @description: constructor.
     * @param tableCount # of tables in the restaurant.
     * @param jobTable restaurant's job table.
     */
    explicit Foyer(unsigned, JobTable &);

    /**
     * @description: copy constructor.
     * @param f foyer we're copying from.
     */
    Foyer(const Foyer &);

    /**
     * @description: copy assignment operator.
     * @param f foyer we're copying from.
     */
    Foyer &operator=(const Foyer &);

    /**
     * @description: removes and returns the ID of the next Table
     * to have a Party.
     * @returns the ID of the Table.
     */
    unsigned getNextTableID();

    /**
     * @description: place a party in the foyer.
     * @param id table # where the party should be seated.
     * @param pPtr a pointer to the party to be seated.
     * @returns true if the Party was placed successfully, false otherwise.
     */
    bool putParty(unsigned, Party *);

    /**
     * @description: remove and return a party from the foyer.
     * @param id table # for a corresponding party to be seated.
     * @returns a pointer to the corresponding party, or nullptr if 
     * no such mapping exists.
     */
    Party *removeParty(unsigned);

    unsigned tableCount_;                    ///< # of restaurant tables.
    std::queue<unsigned> nextTableIDs_;      ///< table indices that are ready to be used.
    std::map<unsigned, Party *> toBeSeated_; ///< map of <Table #, Party*> pairs
    mutable std::mutex m_;                   ///< foyer mutex.
    JobTable &jobTable_;                     ///< used to interface with waiters.

private:
    /**
     * @description: builds the table ID queue.
     * should only be called once when Foyer is first created.
     */
    void prepSeatingQueue();
};

#endif // FOYER_H