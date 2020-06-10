#ifndef PARTY_HPP
#define PARTY_HPP

#include "Restaurant.hpp"
#include "Status.hpp"
#include <vector>
#include <thread>
#include <string>
#include <future>
#include <condition_variable>
#include <mutex>

class Restaurant;
class Guest;
class Waiter;
class Table;
class Menu;

/**
 * @class Party
 * @description: Undergoes the Restaurant experience while managing a group of Guests.
 * @author ajm
 * @created: 1/28/20
 * @modified: 6/2/20
 **/
class Party
{
public:
    class WaiterAccess
    {
        inline static void setWaiter(Party *p, Waiter *w)
        {
            p->theWaiter_ = w;
        }
        inline static void setTable(Party *p, Table *t)
        {
            p->theTable_ = t;
        }
        inline static void setMenu(Party *p, Menu *m)
        {
            p->theMenu_ = m;
        }
        static void signalServiceStarted(Party *);

        friend class Waiter;
    };

    /**
     * @description: constructor.
     * @param r the restaurant.
     * @param gCount number of guests assigned to the party.
     * @param pid the party's unique ID.
     */
    Party(Restaurant &, unsigned, std::string);

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
     * @description: sends out a notification for service.
     */
    void awaitService();

    /**
     * @description: accessor method for party's service flag.
     * @returns whether or not this party has been serviced.
     */
    inline bool checkServiceFlag() { return hasBeenServiced_; }

    /**
     * accessor for this Party's identifier.
     */
    std::string getPID() { return pid_; }

private:
    Restaurant &theRestaurant_;         ///< a reference to the restaurant.
    mutable std::mutex m_;              ///< party's mutex.
    std::condition_variable cv_;        ///< party's condition variable.
    std::thread mthread_;               ///< party's thread.
    std::string pid_;                   ///< the party's unique identifier.
    std::vector<Guest const *> guests_; ///< pointer can't change, but Guest can.
    Waiter *theWaiter_;                 ///< the waiter.
    Table *theTable_;                   ///< the table.
    Menu *theMenu_;                     ///< the menu.
    bool hasBeenServiced_;              ///< service flag.

    Party(const Party &) = delete;
    Party &operator=(const Party &) = delete;

    //need a socket object (?)
};

#endif // PARTY_HPP

/**
 * TODO write a method buildGuests(), or should Guests be passed in?
 * 
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