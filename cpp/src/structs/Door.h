#ifndef DOOR_H
#define DOOR_H

#include "Foyer.h"
#include <queue>
#include <mutex>
#include <future>
#include <condition_variable>
#include <sys/socket.h>

class Party;
class Waiter;

/**
 * @class <code>Door</code>
 * @description: Enables concurrent entry and exit to the restaurant.
 * @author ajm
 * @created: 2/6/20
 * @modified: 6/2/20
 **/
class Door
{
public:
    /**
     * @description: default constructor.
     */
    Door();

    /**
     * @description: constructor.
     * @param f the restaurant foyer.
     **/
    Door(Foyer &);

    /**
     * @description: copy constructor.
     * @param d Door we're copying from.
     * NOTE we will need to keep an eye on how our program responds
     * when copying mutable objects (i.e. mutex)
     */
    Door(const Door &);

    /**
     * @description: copy assignment operator.
     * @param d Door we're copying from.
     * NOTE same as above.
     */
    Door &operator=(const Door &);

    /**
     * @description: destructor.
     **/
    ~Door() {}

    /**
     * @description: initializes member data accordingly.
     */
    void init();

    /**
     * @description: accessor to entry mutex.
     * @note blocks until mutex is free.
     **/
    inline std::mutex &getEntryMutex() const { return mIn_; }

    /**
     * @description: accessor to exit mutex.
     * @note blocks until mutex is free.
     **/
    inline std::mutex &getExitMutex() const { return mOut_; }

    /**
     * @description: accessor to entry queue.
     * @note blocks until entry mutex is free.
     **/
    inline std::queue<Party *> &getEntryQueue() const { return comingIn_; }

    /**
     * @description: accessor to exit queue.
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
    mutable std::queue<Party *> comingIn_; ///< queue of incoming parties.
    mutable std::queue<Party *> goingOut_; ///< queue of outgoing parties.
    mutable std::mutex mIn_;               ///< synchronizes access to incoming queue.
    mutable std::mutex mOut_;              ///< synchronizes access to outgoing queue.
    std::condition_variable cvIn_;         ///< for parties coming in.
    std::condition_variable cvOut_;        ///< for parties going out.
    Foyer &foyer_;                         ///< where parties wait to be seated.
};

#endif // DOOR_H

/**
 * NOTE: Door should not be copyable or moveable.
 * It is shared amongst guests/workers by way of
 * pointers.
 **/