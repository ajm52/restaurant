#ifndef SIMULATION_H
#define SIMULATION_H

#include "Restaurant.h"
#include <iostream>

/**
 * @class <code>Simulation</code>
 * @description: Contains the restaurant simulation.
 * @author ajm
 * @created: 2/6/20
 * @modified: 3/2/20
 **/
class Simulation
{
public:
    /**
     * @description: <code>Simulation</code> constructor.
     **/
    Simulation();

    /**
     * @description: <code>Simulation</code> copy constructor.
     * @note deleted; simulations should not be copied.
     **/
    Simulation(const Simulation &) = delete;

    /**
     * @description: <code>Simulation</code> copy assignment operator.
     * @note deleted; simulations should not be copied.
     **/
    Simulation &operator=(const Simulation &) = delete;

    /**
     * @description: <code>Simulation</code> destructor.
     **/
    ~Simulation() {}

    /**
     * @description: Initializes and prepares data.
     **/
    void init();

    /**
     * @description: Runs the simulation.
     **/
    void run();

    /**
     * @description: Accessor for <code>this Simulation</code>'s restaurant.
     **/
    inline Restaurant *getRestaurant() { return (&restaurant_); }

private:
    Restaurant restaurant_; ///< where dreams become reality.
};

#endif // SIMULATION_H

/**
 * NOTE: May need to modify dtor in the future to clean up used memory.
 **/