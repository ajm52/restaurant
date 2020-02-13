#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Door.h"
#include "Foyer.h"

/**
 * Contains all the elements of a restaurant emulation.
 * 
 * author: ajm
 * created: 2/6/20
 * last modified: 2/6/20
 **/
class Restaurant
{
public:
    Restaurant() : door_(), foyer_() {}
    Restaurant(const Restaurant &) = delete;
    Restaurant &operator=(const Restaurant &) = delete;
    ~Restaurant() {}
    inline const Door &getDoor() const { return door_; }
    inline const Foyer &getFoyer() const { return foyer_; }

private:
    Door door_;
    Foyer foyer_;
};

#endif // RESTAURANT_H