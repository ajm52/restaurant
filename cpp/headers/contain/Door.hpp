#ifndef DOOR_HPP
#define DOOR_HPP

#include <queue>
#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>

class Party;

/**
 * @class Door
 * @description: Enables concurrent entry and exit to the restaurant.
 * @author ajm
 **/
class Door
{
public:
    /**
     * @description: default constructor.
     */
    Door();

    /**
     * @description: copy constructor.
     * @param d door we're copying
     */
    Door(const Door &);

    /**
     * @description: copy assignment operator.
     * @param d door we're copying
     * @returns a reference to this door.
     */
    Door &operator=(const Door &);

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
     * @returns the entry mutex.
     * @note blocks until mutex is free.
     **/
    inline std::mutex &getEntryMutex() { return mIn_; }

    /**
     * @description: accessor to exit mutex.
     * @returns the exit mutex.
     * @note blocks until mutex is free.
     **/
    inline std::mutex &getExitMutex() const { return mOut_; }

    /**
     * @description: accessor to entry queue.
     * @returns the entry queue.
     * @note blocks until entry mutex is free.
     **/
    inline std::queue<std::shared_ptr<Party>> &getEntryQueue() { return comingIn_; }

    /**
     * @description: accessor to exit queue.
     * @returns the exit queue.
     * @note blocks until exit mutex is free.
     **/
    inline std::queue<std::shared_ptr<Party>> &getExitQueue() { return goingOut_; }

    /**
     * @description: CV accessor.
     * @returns the condition variable.
     */
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