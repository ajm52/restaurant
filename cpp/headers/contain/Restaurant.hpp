#ifndef RESTAURANT_HPP
#define RESTAURANT_HPP

#include "GlobalClock.hpp"
#include "Door.hpp"
#include "Foyer.hpp"
#include "Waiter.hpp"
#include "JobTable.hpp"
#include "Table.hpp"
#include "Doorman.hpp"
#include "Menu.hpp"
#include <vector>
#include <memory>

/**
 * @class Restaurant
 * @description: Contains all the elements of a restaurant simulation.
 * @author ajm
 **/
class Restaurant
{
public:
    /**
     * @description: constructor.
     * @param clock the simulation clock.
     * @param menu the restaurant menu.
     * @param tCount table count.
     * @param wCount waiter count.
     * @param pCount party count.
     */
    Restaurant(GlobalClock &, std::shared_ptr<Menu>, unsigned = 0, unsigned = 0, unsigned = 0);

    /**
     * @description: copy constructor.
     * @param r restaurant we're copying from.
     */
    Restaurant(const Restaurant &);

    /**
     * @description: copy assignment operator.
     * @param r restaurant we're copying from.
     */
    Restaurant &operator=(const Restaurant &);

    /**
     * @description: destructor.
     */
    ~Restaurant();

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
    inline Door const &getDoor() const
    {
        return static_cast<Door const &>(door_);
    }

    /**
     * @description: door accessor for non-const access.
     * @returns the door.
     */
    inline Door &getDoor() { return door_; }

    /**
     * @description: foyer accessor.
     * @returns the foyer.
     */
    inline Foyer &getFoyer() { return foyer_; }

    /**
     * @description: menu accessor.
     * @returns a pointer to the menu.
     */
    inline std::shared_ptr<Menu> getMenu() { return menu_; }

    /**
     * @description: clock accessor.
     * @returns a clock reference.
     */
    inline GlobalClock &getClock() { return clock_; }

private:
    GlobalClock &clock_; ///< simulation clock.
    /**
     * primitives.
     */
    unsigned tableCount_;  ///< # of tables in restaurant.
    unsigned waiterCount_; ///< # of waiters in restaurant.
    unsigned partyCount_;  ///< # of parties in the simulation.

    /**
     * user-defined containers.
     */
    JobTable jobTable_;                          ///< communication interface for waiters.
    Foyer foyer_;                                ///< the foyer.
    Door door_;                                  ///< the door.
    std::shared_ptr<Menu> menu_;                 ///< the restaurant menu.
    std::vector<std::shared_ptr<Table>> tables_; ///< the restaurant's tables.

    /**
     * threaded actor(s).
     */
    std::vector<std::shared_ptr<Waiter>> waiters_; ///< waiter staff.
    Doorman doorman_;                              ///< the restaurant's doorman.
};

#endif // RESTAURANT_HPP

/**
 * TODO investigate the need for having const and non-const getters.
 * TODO make Restaurant uncopyable, but moveable.
 */