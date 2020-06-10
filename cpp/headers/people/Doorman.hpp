#ifndef DOORMAN_HPP
#define DOORMAN_HPP

#include "Door.hpp"
#include "Foyer.hpp"
#include "JobTable.hpp"
#include <vector>

/**
 * @class Doorman 
 * @author ajm
 * @created: 6/4/20
 * @modified: 6/7/20
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
    Doorman(Door &d, Foyer &f, JobTable &jt) : d_(d), f_(f), jt_(jt) {}

    /**
     * @description: spins up the Doorman thread.
     **/
    void init();

    /**
     * the Doorman thread's callable.
     **/
    void controlInbound();

    void controlOutbound();

private:
    Door &d_;      ///< how people come and go.
    Foyer &f_;     ///< where parties are placed for seating.
    JobTable &jt_; ///< for notifying waiters of incoming parties.
};
#endif // DOORMAN_HPP