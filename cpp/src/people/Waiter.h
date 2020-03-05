#ifndef WAITER_H
#define WAITER_H

#include "Person.h"
#include "Worker.h"
#include "Multiplexer.h"

/**
 * @class <code>Waiter</code>
 * @description: A restaurant waiter. Inherits from <code>Worker</code>.
 * @author ajm
 * @created: 2/19/20
 * @modified: 3/4/20
 */
class Waiter : public Worker
{
public:
    /**
     * @description: constructor.
     * @param id waiter id string.
     * @param fd waiter fd.
     */
    Waiter(std::string id, int fd) : Worker(fd, id) {}

    /**
     * @description: Registers waiter's main FD in Multiplexer.
     * @returns true on success, false otherwise.
     */
    bool registerMainFD();

    /**
     * @description: Registers a party FD in Multiplexer.
     * @param fd party fd to register.
     * @returns true on success, false otherwise.
     */
    bool registerPartyFD(int);

private:
    Multiplexer selector_; ///< I/O multiplexer.
};

/**
 * waiter read FDs:
 * [0] -> main FD (will be written to by the entry Door hook)
 * 
 * [1] -> kitchen FD (will be written to by Cooks)
 * 
 * [2] -> bar FD (will be written to by Bartenders)
 * 
 * [3...] -> written to and from by Parties that come and go.
 * when a Party leaves, its FD must be removed.
 * 
 * When a waiter is assigned a new Party, it takes the FD from
 * Foyer, registers it as a read socket in its Multiplexer, and
 * writes a Greeting.
 * 
 * TODO: 
 * - add private member pointer to Foyer.
 * - add access to Tables.
 * 
 * LATER:
 * - add access to Kitchen.
 * - add access to Bar.
 */
#endif // WAITER_H