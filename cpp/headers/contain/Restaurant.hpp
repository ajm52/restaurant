#ifndef RESTAURANT_HPP
#define RESTAURANT_HPP

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
 * Contains all the elements of a restaurant emulation.
 * @author ajm
 **/
class Restaurant
{
public:
    /**
     * @description: constructor.
     * @param tCount table count.
     * @param wCount waiter count.
     * @param pCount party count.
     * @param menu the restaurant menu.
     */
    Restaurant(std::shared_ptr<Menu>, unsigned = 0, unsigned = 0, unsigned = 0);

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

private:
    unsigned tableCount_;                          ///< # of tables in restaurant.
    unsigned waiterCount_;                         ///< # of waiters in restaurant.
    unsigned partyCount_;                          ///< # of parties in the simulation.
    JobTable jobTable_;                            ///< communication interface for waiters.
    Foyer foyer_;                                  ///< the foyer.
    Door door_;                                    ///< the door.
    std::vector<std::shared_ptr<Table>> tables_;   ///< the restaurant's tables.
    std::vector<std::shared_ptr<Waiter>> waiters_; ///< waiter staff.
    Doorman doorman_;                              ///< the restaurant's doorman.
    std::shared_ptr<Menu> menu_;                   ///< the restaurant menu.
};

#endif // RESTAURANT_HPP