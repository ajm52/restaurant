#include "Simulation.h"
#include "Party.cpp"
#include <memory>
#include <iostream>
#include <vector>

Simulation::Simulation() : restaurant_()
{
    init();
}

void Simulation::run()
{
    // spawn a thread-based Party and get it to enter the Door.
    std::vector<const Guest *> guests;
    std::shared_ptr<Party> pP(new Party(&guests, getRestaurant(), "P1"));
    std::cout << "party has spawned\n";
}

void Simulation::init()
{
    run();
}