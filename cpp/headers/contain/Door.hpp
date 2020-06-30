#ifndef DOOR_HPP
#define DOOR_HPP

#include <queue>
#include <mutex>
#include <memory>
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
     * @description: constructor.
     */
    Door() : mIn_(),
             mOut_(),
             comingIn_(),
             goingOut_(),
             cv_() {}

    /**
     * @description: destructor.
     **/
    ~Door() = default;

    /**
     * @description: accessor to entry mutex.
     * @returns the entry mutex.
     * @note blocks until mutex is free.
     **/
    inline std::mutex &getEntryMutex() const { return mIn_; }

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
    inline std::condition_variable &getCV() const { return cv_; }

    Door(const Door &) = delete; ///< Door is uncopyable and unmoveable.
    Door &operator=(const Door &) = delete;
    Door(Door &&) = delete;
    Door &operator=(Door &&) = delete;

private:
    mutable std::mutex mIn_;                      ///< synchronizes access to incoming queue.
    mutable std::mutex mOut_;                     ///< synchronizes access to outgoing queue.
    std::queue<std::shared_ptr<Party>> comingIn_; ///< queue of incoming parties.
    std::queue<std::shared_ptr<Party>> goingOut_; ///< queue of outgoing parties.
    mutable std::condition_variable cv_;          ///< for parties going in and out (waited on by doorman)
};

#endif // DOOR_HPP