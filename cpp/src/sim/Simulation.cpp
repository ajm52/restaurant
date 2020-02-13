#include "Party.cpp"
#include "Simulation.h"

#include <memory>
#include <iostream>
#include <vector>

Simulation::Simulation() : restaurant_()
{
    init();
}

void Simulation::run()
{
    // spawn a thread-based Party and get it to enter via the Door.
    std::cout << "spawning party\n";
    std::vector<const Guest *> guests;
    std::shared_ptr<Party> pP(new Party(getRestaurant(), guests));
    std::cout << "after spawn\n";
}

void Simulation::init()
{
    run();
}