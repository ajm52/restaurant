#ifndef RESTAURANT_HPP
#define RESTAURANT_HPP

#include "GlobalClock.hpp"
#include "OrderMachine.hpp"
#include "Door.hpp"
#include "Foyer.hpp"
#include "Waiter.hpp"
#include "JobTable.hpp"
#include "Table.hpp"
#include "Doorman.hpp"
#include <vector>
#include <memory>

class Menu;

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
    Restaurant(GlobalClock &, Menu &, unsigned = 0, unsigned = 0, unsigned = 0);

    /**
     * @description: destructor.
     */
    ~Restaurant() = default;

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
    inline const unsigned tableCount() const { return tableCount_; }

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
     * @returns a reference to the menu.
     */
    inline const Menu &getMenu() const { return menu_; }

    /**
     * @description: clock accessor.
     * @returns a clock reference.
     */
    inline GlobalClock &getClock() { return clock_; }

    Restaurant(const Restaurant &) = delete; ///< Restaurant is uncopyable and unmovable.
    Restaurant &operator=(const Restaurant &) = delete;
    Restaurant(Restaurant &&) = delete;
    Restaurant &operator=(Restaurant &&) = delete;

private:
    GlobalClock &clock_;

    unsigned tableCount_;
    unsigned waiterCount_;
    unsigned partyCount_;

    JobTable jobTable_; ///< comm interface for waiters.
    Foyer foyer_;
    Door door_;
    OrderMachine om_;
    Menu &menu_;
    std::vector<std::shared_ptr<Table>> tables_;

    //ANCHOR look into typedef for this^^^

    std::vector<std::shared_ptr<Waiter>> waiters_;
    Doorman doorman_;
};

#endif // RESTAURANT_HPP

/**
 * TODO add mem var for Bartenders
 * TODO write func buildBartenders()
 */