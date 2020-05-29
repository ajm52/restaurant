#ifndef DOOR_H
#define DOOR_H

#include "Foyer.h"
#include <boost/signals2.hpp>
#include <queue>
#include <mutex>
#include <future>
#include <sys/socket.h>

class SimLoader;
class Party;
class Waiter;

/**
 * @struct <code>EntrySlot</code>
 * @description: Entry callback used by <code>Door</code>.
 * @author ajm
 * @created: 2/13/20
 * @modified: 3/2/20
 **/
struct EntrySlot
{
    /**
     * @description: Callback for a party's arrival.
     * <p>
     * Moves parties from entry queue to the foyer.
     * For each moved party, a waiter is messaged.
     * 
     * @note blocks until entry mutex is free.
     **/
    void operator()(Foyer *, Party *);
};

/**
 * @struct <code>ExitSlot</code>
 * @description: Exit callback used by <code>Door</code>.
 * @author ajm
 * @created: 2/13/20
 * @modified: 2/13/20
 **/
struct ExitSlot
{
    /**
     * @description: Callback for a party's exit.
     **/
    void operator()();
};

/**
 * @class <code>Door</code>
 * @description: Enables concurrent entry and exit to the restaurant.
 * @author ajm
 * @created: 2/6/20
 * @modified: 3/4/20
 **/
class Door
{
public:
    /**
     * @class LoaderAccess
     * @description: Allows SimLoader to set the door's FD
     * in a relatively safe manner.
     * @author ajm
     * @created: 3/4/20
     * @modified: 5/29/20
     */
    class LoaderAccess
    {
        static void setFD(Door *d, int fd) { d->fd_ = fd; }
        friend class SimLoader;
    };

    /**
     * @description: <code>Door</code> constructor.
     * Initializes member data appropriately.
     **/
    Door();

    /**
     * @description: <code>Door</code> destructor.
     **/
    ~Door() {}

    /**
     * @description: <code>Door</code> entry signal function.
     * Calls the entry signal, triggering a callback.
     **/
    void signalEntry();

    /**
     * @description: <code>Door</code> exit signal function.
     * Calls the exit signal, triggering a callback.
     **/
    void signalExit() { exitSig_(); }

    /**
     * @description: accessor to <code>this Door</code>'s entry mutex.
     * @note blocks until mutex is free.
     **/
    inline std::mutex &getEntryMutex() const { return mIn_; }

    /**
     * @description: accessor to <code>this Door</code>'s exit mutex.
     * @note blocks until mutex is free.
     **/
    inline std::mutex &getExitMutex() const { return mOut_; }

    /**
     * @description: accessor to <code>this Door</code>'s entry queue.
     * @note blocks until entry mutex is free.
     **/
    inline std::queue<Party *> &getEntryQueue() const { return comingIn_; }

    /**
     * @description: accessor to <code>this Door</code>'s exit queue.
     * @note blocks until exit mutex is free.
     **/
    inline std::queue<Party *> &getExitQueue() const { return goingOut_; }

    /**
     * @description: queues a Party for service while returning 
     * access to their Waiter.
     * @param p the Party that needs service.
     * @returns the Waiter that will be servicing.
     */
    Waiter *queueForService(Party *);

private:
    mutable std::queue<Party *> comingIn_;                     ///< queue of incoming parties.
    mutable std::queue<Party *> goingOut_;                     ///< queue of outgoing parties.
    mutable std::mutex mIn_;                                   ///< synchronizes access to incoming queue.
    mutable std::mutex mOut_;                                  ///< synchronizes access to outgoing queue.
    boost::signals2::signal<void(Foyer *, Party *)> entrySig_; ///< entry signal.
    boost::signals2::signal<void()> exitSig_;                  ///< exit signal.
    EntrySlot entrySlot_;                                      ///< entry callback.
    ExitSlot exitSlot_;                                        ///< exit callback.
    int fd_;                                                   ///< door fd; used to message waiters.
    Foyer foyer_;                                              ///< where parties wait to be seated.
};

#endif // DOOR_H

/**
 * NOTE: Door should not be copyable or moveable.
 * It is shared amongst guests/workers by way of
 * pointers.
 **/