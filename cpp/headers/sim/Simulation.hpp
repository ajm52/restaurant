#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "GlobalClock.hpp"
#include "Restaurant.hpp"
#include "Party.hpp"
#include "Menu.hpp"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <memory>
#include <map>

/**
 * @class Simulation
 * @description: Contains the restaurant simulation.
 * @author ajm
 **/
class Simulation
{
public:
    /**
     * @description: constructor.
     **/
    Simulation();

    /**
     * @description: copy constructor.
     **/
    Simulation(const Simulation &) = default;

    /**
     * @description: copy assignment operator.
     * @returns this simulation.
     **/
    Simulation &operator=(const Simulation &) = default;

    /**
     * @description: destructor.
     **/
    ~Simulation() = default;

    /**
     * @description: Initializes and prepares basic simulation data.
     * @param filepath sim config filepath.
     **/
    void init(std::string);

    /**
     * @description: factory method for generating the restaurant menu.
     * @param filepath the menu config filepath.
     * @returns a shared pointer that holds the menu.
     */
    std::shared_ptr<Menu> createMenu(std::string);

    /**
     * @description: Runs the simulation.
     **/
    void run();

    /**
     * @description: builds the simulation's parties.
     */
    void buildSimParties(Restaurant &);

private:
    unsigned partyCount_;                            ///< max sim party count.
    unsigned waiterCount_;                           ///< max sim waiter count.
    unsigned tableCount_;                            ///< max sim table count.
    std::vector<std::shared_ptr<Party>> simParties_; ///< sim parties.
    std::vector<unsigned> partiesInside_;            ///< IDs of parties inside restaurant.
    std::vector<unsigned> partiesOutside_;           ///< IDs of parties outside restaurant.
    GlobalClock clock_;                              ///< simulation clock.
};

#endif // SIMULATION_HPP

/**
 * NOTE: May need to modify dtor in the future to clean up used memory.
 **/