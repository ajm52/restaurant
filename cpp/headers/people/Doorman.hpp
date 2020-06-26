#ifndef DOORMAN_HPP
#define DOORMAN_HPP

#include "Door.hpp"
#include "GlobalClock.hpp"
#include "Foyer.hpp"
#include "JobTable.hpp"
#include <vector>
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
     * @param d restaurant door
     * @param f restaurant foyer
     * @param jt restaurant jobtable
     * NOTE all parameters must be instantiated before this object.
     **/
    Doorman(Door &d, Foyer &f, JobTable &jt, GlobalClock &gc) : d_(d), f_(f), jt_(jt), gc_(gc) {}

    /**
     * @description: spins up the Doorman thread.
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
 */