#include <iostream>

#include "Restaurant.h"
#include "Party.h"
#include "Simulation.h"

Simulation::Simulation(Restaurant &restaurant) : restaurant_(restaurant)
{
    init();
}

void Simulation::init()
{
    run();
}

void Simulation::run()
{
    // spawn a thread-based Party and get it to enter via the Door.
    std::cout << "spawning party\n";
    Party party(getRestaurant());
    std::cout << "after spawn\n";
}