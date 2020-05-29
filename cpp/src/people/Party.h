#ifndef PARTY_H
#define PARTY_H

#include "Status.h"
#include <vector>
#include <thread>
#include <string>

class Restaurant;
class Guest;
class Waiter;
class Table;

/**
 * @description: Undergoes the Restaurant experience while managing a group of Guests.
 * @author ajm
 * @created: 1/28/20
 * @modified: 5/26/20
 **/
class Party
{
public:
    Party(Restaurant &, const std::vector<Guest const *> &, std::string); // main ctor
    Party(Restaurant *, std::vector<Guest const *> *, std::string);       // for thread debugging

    /**
    * boots up the Party thread.
    **/
    void init();

    /**
    * main thread of execution for Party.
    **/
    void run();

    /**
    * used by parties to enter the restaurant.
    */
    void enterRestaurant();

    /**
     * this method triggers an asynchronous callback 
     * meant to queue this Party for table service.
     * @returns a Waiter for this Party.
     */
    Waiter *awaitService();

    /**
     * accessor for this Party's identifier.
     */
    inline std::string getPID() { return pid_; }

private:
    std::string pid_;                   ///< the party's unique identifier.
    Status::Party status_;              ///< describes party state
    std::vector<Guest const *> guests_; ///< pointer can't change, but Guest can.
    Restaurant &theSpot_;               ///< where we're headed.

    //need a socket object (?)
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