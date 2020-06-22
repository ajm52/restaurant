#ifndef PARTY_HPP
#define PARTY_HPP

#include "Restaurant.hpp"
#include "GlobalClock.hpp"
#include <vector>
#include <thread>
#include <string>
#include <future>
#include <condition_variable>
#include <mutex>
#include <memory>

class Guest;
class Waiter;
class Table;
class Menu;

/**
 * @class Party
 * @description: Undergoes the Restaurant experience while managing a group of Guests.
 * @author ajm
 **/
class Party
{
public:
    /**
     * @class WaiterAccess
     * @description: used to give Waiters relatively safe access to specific Party member data.
     * @author ajm
     */
    class WaiterAccess
    {

        /**
         * @description: used by Waiters to tell Parties who their Waiter is.
         * @param p party.
         * @param w waiter.
         */
        inline static void setWaiter(Party *p, std::shared_ptr<Waiter> w)
        {
            p->theWaiter_ = w;
        }

        /**
         * @description: used by Waiters to provide Tables for Parties.
         * @param p table receiver.
         * @param t restaurant table.
         */
        inline static void setTable(Party *p, std::shared_ptr<Table> t)
        {
            p->theTable_ = t;
        }

        /**
         * @description: used by Waiters to provide Menus for Parties
         * @param p menu receiver.
         * @param m restaurant menu.
         */
        inline static void setMenu(Party *p, std::shared_ptr<Menu> m)
        {
            p->theMenu_ = m;
        }

        /**
         * @description: used by Waiters to signal Parties.
         * @param p signal receiver.
         */
        static void signalServiceStarted(Party *);

        friend class Waiter;
    };

    /**
     * @description: constructor.
     * @param gc simulation clock.
     * @param r the restaurant.
     * @param gCount number of guests assigned to the party.
     * @param pid the party's unique ID.
     */
    Party(GlobalClock &, Restaurant &, unsigned, std::string);

    /**
     * @description: move constructor.
     * @param p party we're moving.
     */
    Party(Party &&);

    /**
     * @description: move assignment operator.
     * @param p party we're moving.
     * @returns a reference to this party.
     */
    Party &operator=(Party &&);

    /**
     * @description: destructor.
     */
    ~Party() = default;

    /**
     * @description: initializes the party thread.
     */
    void init();

    /**
     * @description: main thread of execution for Party.
     */
    void run();

    /**
     * @description: enters this party into the restaurant queue.
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
     * @description: PID accessor.
     * @returns this party's PID string.
     */
    inline std::string &getPID() { return pid_; }

    /**
     * @description: clock accessor.
     * @returns the simulation clock.
     */
    inline GlobalClock &getClock() { return clock_; }

    /**
     * @description: factory method for creating Parties.
     * @param gc simulation clock.
     * @param r the restaurant.
     * @param gCount # of guests.
     * @param pid unique party id.
     * @returns a smart pointer to this party.
     */
    static std::shared_ptr<Party> makeParty(GlobalClock &, Restaurant &, unsigned, std::string);

private:
    GlobalClock &clock_;        ///< simulation clock.
    Restaurant &theRestaurant_; ///< a reference to the restaurant.

    /**
     * Party-specific data variables
     */
    std::string pid_;                            ///< the party's unique identifier.
    std::vector<std::shared_ptr<Guest>> guests_; ///< party guests.
    std::shared_ptr<Waiter> theWaiter_;          ///< the waiter.
    std::shared_ptr<Table> theTable_;            ///< the table.
    std::shared_ptr<Menu> theMenu_;              ///< the menu.

    /**
     * Synchronization/Threading variables
     */
    bool hasBeenServiced_;       ///< service flag.
    std::mutex m_;               ///< party's mutex.
    std::condition_variable cv_; ///< party's condition variable.
    std::thread mthread_;        ///< party's thread.

    /**
     * @description: inaccessible copy constructor; Parties shouldn't be copyable, as they are threaded.
     */
    Party(const Party &) = delete;

    /**
     * @description: inaccessible copy assignment operator.
     */
    Party &operator=(const Party &) = delete;
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