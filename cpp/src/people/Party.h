#ifndef PARTY_H
#define PARTY_H

#include <vector>
#include <thread>

#include "Status.h"

class Restaurant;
class Guest;

/**
 * manages a group of guests.
 * 
 * author: ajm
 * created: 1/28/20
 * last modified: 2/6/20
 **/
class Party
{
public:
    Party(Restaurant &, const std::vector<Guest const *> &); // main ctor
    Party(Restaurant &, std::vector<Guest const *> *);       // for thread debugging
    void init();
    void run();

private:
    Status::Party status_;              // describes party state
    std::vector<Guest const *> guests_; // pointer can't change, but Guest can.
    Restaurant &theSpot_;               // where we're headed!
    //need a socket object.
};

#endif // PARTY_H

/**
 * TODO: write a method updateStatus.
 *      - after changing its Status, Party should get a factory-generated Activity
 *      and send it off to the front-end updating interface.
 * 
 * TODO: write methods for interacting with the Waiter.
 * 
 * TODO: write methods for entering/exiting restaurant.
 *      - should these be member functions? Why or why not?
 * 
 * TODO: implement thread capabilities
 *      - define the Party's "lifetime" (what should the "run" function look like?)
 *      - how should this be represented with code?
 * 
 * TODO: implement socket capabilities
 *      - have its own socket
 *      - have a set of message response functions (pertaining to DRY)
 * 
 * TODO: write test cases for member data, threading, and socket I/O.
 **/