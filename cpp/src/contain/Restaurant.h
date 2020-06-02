#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Door.h"
#include "Foyer.h"
#include "Waiter.h"
#include "WorkerBulletin.h"
#include "JobTable.h"
#include "Table.h"
#include <vector>

class SimLoader;

/**
 * Contains all the elements of a restaurant emulation.
 * 
 * author: ajm
 * created: 2/6/20
 * last modified: 6/1/20
 **/
class Restaurant
{
public:
    /**
     * @description: constructor.
     * @param tCount table count.
     * @param wCount waiter count.
     * @param pCount party count.
     */
    Restaurant(unsigned = 0, unsigned = 0, unsigned = 0);

    /**
     * @description: deleted copy constructor.
     * no reason to copy construct this class.
     */
    Restaurant(const Restaurant &) = delete;

    /**
     * @description: deleted copy assignment operator.
     * no reason to copy assign this class.
     */
    Restaurant &operator=(const Restaurant &) = delete;

    /**
     * @description: destructor.
     */
    ~Restaurant() {}

    /**
     * @description: initializes sim parameters.
     */
    void init();

    /**
     * @description: responsible for building 
     * the restaurant's tables.
     */
    void buildTables();

    /**
     * @description: responsible for building
     * the restaurant's waiters.
     */
    void buildWaiters();

    /**
     * @description: Accessor for # of tables in restaurant.
     * @returns # of restaurant tables.
     */
    inline unsigned tableCount() { return tableCount_; }

    /**
     * @description: door accessor for const access.
     * @returns a const pointer to the door.
     */
    inline Door const *getDoor() const
    {
        return static_cast<Door const *>(&door_);
    }

    /**
     * @description: door accessor for non-const access.
     * @returns a pointer to the door.
     */
    inline Door *getDoor() { return &door_; }

    /**
     * @description: foyer accessor.
     * @returns a pointer to the foyer.
     */
    inline Foyer *getFoyer() { return &foyer_; }

private:
    unsigned tableCount_;         ///< # of tables in restaurant.
    unsigned waiterCount_;        ///< # of waiters in restaurant.
    unsigned partyCount_;         ///< # of parties in the simulation.
    JobTable jobTable_;           ///< communication interface for waiters.
    Foyer foyer_;                 ///< the foyer.
    Door door_;                   ///< the door.
    std::vector<Table> tables_;   ///< the restaurant's tables.
    std::vector<Waiter> waiters_; ///< waiter staff.
};

#endif // RESTAURANT_H