#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "Restaurant.hpp"
#include "SimLoader.hpp"
#include "Party.hpp"
#include <iostream>
#include <vector>
#include <unordered_set>

/**
 * @class <code>Simulation</code>
 * @description: Contains the restaurant simulation.
 * @author ajm
 * @created: 2/6/20
 * @modified: 6/3/20
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
     * @note deleted; simulations should not be copied.
     **/
    Simulation(const Simulation &) = delete;

    /**
     * @description: copy assignment operator.
     * @note deleted; simulations should not be copied.
     **/
    Simulation &operator=(const Simulation &) = delete;

    /**
     * @description: destructor.
     **/
    ~Simulation() {}

    /**
     * @description: Initializes and prepares data.
     * @param filepath sim config filepath.
     **/
    void init(std::string);

    /**
     * @description: Runs the simulation.
     **/
    void run();

    /**
     * @description: builds the simulation's parties.
     */
    void buildSimParties(Restaurant &);

private:
    unsigned partyCount_;                  ///< max sim party count.
    unsigned waiterCount_;                 ///< max sim waiter count.
    unsigned tableCount_;                  ///< max sim table count.
    std::vector<Party> simParties_;        ///< sim parties.
    std::vector<unsigned> partiesInside_;  ///< IDs of parties inside restaurant.
    std::vector<unsigned> partiesOutside_; ///< IDs of parties outside restaurant.
};

#endif // SIMULATION_HPP

/**
 * NOTE: May need to modify dtor in the future to clean up used memory.
 **/