#ifndef SIMULATION_H
#define SIMULATION_H

class Restaurant;

/**
 * main container of the Restaurant simulation.
 * 
 * author: ajm
 * created: 2/6/20
 * last modified: 2/6/20
 **/
class Simulation
{
public:
    // ctor, dtor, copy control
    Simulation(Restaurant &restaurant);
    Simulation &operator=(const Simulation &) = delete;
    Simulation(const Simulation &) = delete;
    ~Simulation() {}

    // emulation funcs
    void init();
    void run();

    // accessors
    inline Restaurant &getRestaurant() { return restaurant_; }

private:
    Restaurant &restaurant_;
};

#endif // SIMULATION_H

/**
 * NOTE: May need to modify dtor in the future to clean up used memory.
 **/