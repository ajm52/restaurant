#include "Simulation.h"
#include "Door.h"
#include "Waiter.h"
#include "Party.cpp"
#include <memory>
#include <iostream>
#include <vector>

Simulation::Simulation() : restaurant_(), parties_(), loader_()
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
    /**
     * initialization synopsis in pseudocode:
     * 
     * - step 1: constructor
     * r = new Restaurant()
     * loader = new SimLoader()
     * 
     * - step 2: door
     * loader.initDoorFD(r.getDoor())
     * 
     * - step 3: waiters
     * waiters = loader.createWaiters()
     * loader.assignWaiters(r,waiters)
     * 
     * - step 4: waiter bulletin
     * loader.loadWorkerBulletin(r.getWaiterBulletin(), waiters)
     * 
     * - step 5: parties
     * parties = loader.createParties(r)
     */
    loader_.initDoorFD(restaurant_.getDoor());

    std::shared_ptr<std::vector<Waiter>> waiters = loader_.createWaiters();
    loader_.initRestaurantWaiters(getRestaurant(), waiters);

    loader_.loadWaiterBulletin(getRestaurant()->getWaiterBulletin(), waiters);

    parties_ = std::move(*(loader_.createParties(getRestaurant())));

    run();
}