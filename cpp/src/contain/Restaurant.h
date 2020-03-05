#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Door.h"
#include "Foyer.h"
#include "Waiter.h"
#include "WorkerBulletin.h"
#include <vector>

class SimLoader;

/**
 * Contains all the elements of a restaurant emulation.
 * 
 * author: ajm
 * created: 2/6/20
 * last modified: 3/4/20
 **/
class Restaurant
{
public:
    /**
     * @class LoaderAccess
     * @description: Allows SimLoader to configure a Restaurant
     * with relative safety and modularity.
     * @author ajm
     * @created: 3/4/20
     * @modified: 3/4/20
     */
    class LoaderAccess
    {
        /**
         * @description: Assigns a given set of waiters to a given restaurant.
         * @param r the restaurant.
         * @param w the waiters.
         */
        static void assignWaiters(Restaurant *, std::vector<Waiter> &);
        friend class SimLoader;
    };
    /**
     * @description: constructor.
     * default initializes practically everything.
     */
    Restaurant() : door_(), foyer_(), waiters_(), waiterBulletin_() {}

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

    /**
     * @description: waiter bulletin accessor.
     * @returns the waiter bulletin.
     */
    inline WorkerBulletin &getWaiterBulletin() { return waiterBulletin_; }

private:
    Door door_;                     ///< the door.
    Foyer foyer_;                   ///< the foyer.
    std::vector<Waiter> waiters_;   ///< waiter staff.
    WorkerBulletin waiterBulletin_; ///< waiter bulletin.
};

#endif // RESTAURANT_H