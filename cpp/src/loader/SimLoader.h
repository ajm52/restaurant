#ifndef SIMLOADER_H
#define SIMLOADER_H

#include "DataLoader.h"

#include <memory>
#include <vector>
#include <string>

class Restaurant;
class Door;
class Party;
class Worker;
class Waiter;
class WorkerBulletin;

/**
 * @class <code>SimLoader</code>
 * @description: Loads the restaurant simulation from metadata.
 * @author ajm
 * @created: 2/19/20
 * @modified: 3/4/20
 */
class SimLoader
{
public:
    /**
     * @description: Default constructor.
     **/
    SimLoader() {}

    /**
     * @description: Destructor.
     **/
    ~SimLoader() {}

    /**
     * @description: Initializes the restaurant door's FD from metadata.
     * @param d Door pointer whose fd needs initializing.
     * @note this method expects door_io_data.md to exist
     * in the 'meta' folder.
     */
    void initDoorFD(Door *);

    /**
     * @description: creates and returns a set of waiters, with the given set of FDs.
     * @returns a shared pointer to a set of newly created waiters.
     * @note expects waiter_io_data.md to exist in 'meta'.
     */
    std::shared_ptr<std::vector<Waiter>> createWaiters();

    /**
     * @description: Initializes the restaurant waiter staff.
     * @param r restaurant to be configured.
     * @param w smart pointer to a set of waiters to be staffed.
     */
    void initRestaurantWaiters(Restaurant *, const std::shared_ptr<std::vector<Waiter>>);

    /**
     * @description: loads a given waiter bulletin with a given set of waiter information.
     * @param wb the bulletin.
     * @param waiters waiters whose data requires loading.
     */
    void loadWaiterBulletin(WorkerBulletin &, const std::shared_ptr<std::vector<Waiter>>);

    /**
     * @description: creates and returns a set of parties with the given set of FDs.
     * @param r pointer to restaurant. needed by created parties.
     * @returns a shared pointer to a set of newly created parties.
     * @note expects party_io_data.md to exist in 'meta'.
     */
    std::shared_ptr<std::vector<Party>> createParties(Restaurant &);

private:
    DataLoader dataLoader_; ///< data-related loading helper.
};

#endif // SIMLOADER_H

/**
 * TODO: write methods to:
 * 
 * - create a set of Guests for each Party.
 * 
 *  - connect each Waiter to the Door's socket;
 * the returned socket will be the first one in
 * the Waiter's Multiplexer read list.
 * 
 *  - creating the Tables.
 *  - creating the Bartender(s).
 *  - creating the Cook(s).
 * 
 * TEST:
 * - initialization of the Door's socket.
 * - creation of Waiters and their sockets.
 */