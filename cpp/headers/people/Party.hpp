#ifndef PARTY_HPP
#define PARTY_HPP

#include "Restaurant.hpp"
#include "GlobalClock.hpp"
#include "SimMonitor.hpp"
#include "Order.hpp"
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
class Party : public std::enable_shared_from_this<Party>
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
        inline static void setWaiter(std::shared_ptr<Party> p, std::shared_ptr<Waiter> w)
        {
            p->theWaiter_ = w;
        }

        /**
         * @description: used by Waiters to provide Tables for Parties.
         * @param p table receiver.
         * @param t restaurant table.
         */
        inline static void setTable(std::shared_ptr<Party> p, std::shared_ptr<Table> t)
        {
            p->theTable_ = t;
        }

        /**
         * @description: used by Waiters to provide Menus for Parties
         * @param p menu receiver.
         * @param m restaurant menu.
         */
        inline static void setMenu(std::shared_ptr<Party> p, std::shared_ptr<Menu> m)
        {
            p->theMenu_ = m;
        }

        /**
         * @description: used by Waiters to signal Parties.
         * @param p signal receiver.
         */
        static void signalServiceStarted(std::shared_ptr<Party>);

        friend class Waiter;
    };

    /**
     * @description: constructor.
     * @param gc simulation clock.
     * @param r the restaurant.
     * @param sm the simulation monitor.
     * @param gCount number of guests assigned to the party.
     * @param pid the party's unique ID.
     */
    Party(GlobalClock &, Restaurant &, SimMonitor &, unsigned, std::string);

    /**
     * @description: destructor.
     * NOTE we will eventually need to implement 
     * a proper destructor, at least for the sake
     * of thread cleanup. 
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
     * @description: sends out a notification for service and waits for a notify.
     */
    void awaitService();

    /**
     * @description: submits menu selections via OrderService
     * and awaits the corresponding Order.
     */
    void awaitOrder();

    /**
     * @description: used to select and submit menu options.
     * @param numOptions # of menu options to be submitted
     * @param type option type being selected.
     */
    void submitSelections(unsigned, char) const;

    /**
     * @description: creates an Order with a set of random options off of the menu.
     * @param count number of options to select.
     * @param type type of option to select from.
     * @returns the created order.
     */
    Order createOrder(unsigned, char);
    //TODO move this method into OrderService

    /**
     * @description: accessor method for party's service flag.
     * @returns whether or not this party has been serviced.
     */
    inline const bool checkServiceFlag() const { return hasBeenServiced_; }

    /**
     * @description: PID accessor.
     * @returns this party's PID string.
     */
    inline const std::string &getPID() const { return pid_; }

    /**
     * @description: clock accessor.
     * @returns the simulation clock.
     */
    inline GlobalClock &getClock() { return clock_; }

    Party(const Party &) = delete; ///< Party is neither copyable nor movable.
    Party &operator=(const Party &) = delete;
    Party(Party &&) = delete;
    Party &operator=(Party &&) = delete;

private:
    GlobalClock &clock_;        ///< simulation clock.
    Restaurant &theRestaurant_; ///< a reference to the restaurant.
    SimMonitor &sm_;            ///< simulation monitor.

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
    mutable bool hasBeenServiced_;       ///< service flag.
    mutable std::mutex m_;               ///< party's mutex.
    mutable std::condition_variable cv_; ///< party's condition variable.
    std::thread mthread_;                ///< party's thread.
};

#endif // PARTY_HPP

/**
 * TODO pass off responsibility of "making an Order" to OrderService; 
 * Parties should only be concerned with making Menu selections. 
 * 
 * TODO write a method buildGuests(), or should Guests be passed in?
 * 
 * TODO write a method updateStatus.
 *      - after changing its Status, Party should get a factory-generated Activity
 *      and send it off to the front-end updating interface.
 * 
 * TODO write a method for exiting restaurant.
 * 
 * TODO implement thread capabilities.
 *      - define the Party's "lifetime" (what should the "run" function look like?)
 *      - how should this be represented with code?
 * 
 * TODO write test cases for member data, threading, and socket I/O. (eventually?)
 **/