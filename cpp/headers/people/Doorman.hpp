#ifndef DOORMAN_HPP
#define DOORMAN_HPP

#include "Door.hpp"
#include "GlobalClock.hpp"
#include "Foyer.hpp"
#include "JobTable.hpp"
#include <thread>

/**
 * @class Doorman 
 * @author ajm
 * @description: Thread-based class that lets people in and out of the restaurant. 
 * Also acts as an adapter between the door queue and the foyer, notifying waiters
 * of parties that need service.
 **/
class Doorman
{
public:
    /**
     * @description: constructor.
     * @param d the door
     * @param f the foyer
     * @param jt the jobtable
     **/
    Doorman(Door &d, Foyer &f, JobTable &jt, GlobalClock &gc)
        : d_(d),
          f_(f),
          jt_(jt),
          gc_(gc) {}

    /**
     * @description: spins up the Doorman threads.
     **/
    void init();

    /**
     * @description: the Doorman thread's callable for handling inbound Parties.
     **/
    void controlInbound();

    /**
     * @description: the Doorman thread's callable for handling outbound Parties.
     **/
    void controlOutbound();

    /**
     * @description: clock accessor.
     * @returns the simulation clock.
     */
    inline GlobalClock &getClock() { return gc_; }

    Doorman(const Doorman &) = delete; ///< Doorman is neither copyable nor movable.
    Doorman &operator=(const Doorman &) = delete;
    Doorman(Doorman &&) = delete;
    Doorman &operator=(Doorman &&) = delete;

private:
    Door &d_;                     ///< how people come and go.
    Foyer &f_;                    ///< where parties are placed for seating.
    JobTable &jt_;                ///< for notifying waiters of incoming parties.
    GlobalClock &gc_;             ///< a global clock.
    std::thread incomingHandler_; ///< prepares incoming parties to be seated.
    std::thread outgoingHandler_; ///< sends parties on their way.
};
#endif // DOORMAN_HPP

/**
 * TODO implement controlOutbound().
 * TODO write destructor (consider thread cleanup)
 */