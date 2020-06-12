#ifndef DOOR_HPP
#define DOOR_HPP

#include <queue>
#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>

class Party;
class Doorman;

/**
 * @class <code>Door</code>
 * @description: Enables concurrent entry and exit to the restaurant.
 * @author ajm
 * @created: 2/6/20
 * @modified: 6/5/20
 **/
class Door
{
public:
    class DoormanAccess
    {
        static void waitForInbound(Door *);
        static void waitForOutbound(Door *);
        friend class Doorman;
    };

    /**
     * @description: default constructor.
     */
    Door();

    Door(const Door &) = default;
    Door &operator=(const Door &) = default;

    /**
     * @description: move constructor.
     * @param d door object we are moving.
     */
    Door(Door &&);

    /**
     * @description: move assignment operator.
     * @param d door object we are moving.
     * @returns a reference to this door.
     */
    Door &operator=(Door &&);

    /**
     * @description: destructor.
     **/
    ~Door() = default;

    /**
     * @description: initializes member data accordingly.
     */
    void init();

    /**
     * @description: accessor to entry mutex.
     * @note blocks until mutex is free.
     **/
    inline std::mutex &getEntryMutex() { return mIn_; }

    /**
     * @description: accessor to exit mutex.
     * @note blocks until mutex is free.
     **/
    inline std::mutex &getExitMutex() const { return mOut_; }

    /**
     * @description: accessor to entry queue.
     * @note blocks until entry mutex is free.
     **/
    inline std::queue<std::shared_ptr<Party>> &getEntryQueue() { return comingIn_; }

    /**
     * @description: accessor to exit queue.
     * @note blocks until exit mutex is free.
     **/
    inline std::queue<std::shared_ptr<Party>> &getExitQueue() { return goingOut_; }

    inline std::condition_variable &getCV() { return cv_; }

private:
    mutable std::mutex mIn_;                      ///< synchronizes access to incoming queue.
    mutable std::mutex mOut_;                     ///< synchronizes access to outgoing queue.
    std::queue<std::shared_ptr<Party>> comingIn_; ///< queue of incoming parties.
    std::queue<std::shared_ptr<Party>> goingOut_; ///< queue of outgoing parties.
    std::condition_variable cv_;                  ///< for parties going in and out (waited on by doorman)
    std::vector<std::shared_ptr<Party>> outside_; ///< parties that are not in the restaurant.
};

#endif // DOOR_HPP