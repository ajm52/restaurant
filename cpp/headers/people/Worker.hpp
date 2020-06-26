#ifndef WORKER_HPP
#define WORKER_HPP

#include "Person.hpp"
#include "JobTable.hpp"
#include "Menu.hpp"
#include "GlobalClock.hpp"
#include <memory>
#include <vector>
#include <string>
#include <thread>

struct SeatingJob;
struct OrderJob;
struct Job;

/**
 * @class Worker
 * @description: A restaurant employee. Inherits from Person.
 * @author ajm
 * @note In order to take full advantage of runtime polymorphism 
 * with the Visitor pattern, all handleJob(Job) methods must be 
 * pure virtual. That said, Worker subclasses must provide
 * definitions for all handleJob methods to make the compiler happy.
 */
class Worker : public Person
{
public:
    /**
     * @description: constructor.
     * @param id worker id string
     * @param gc simulation clock
     * @param jt job table
     * @param m restaurant menu
     * 
     */
    Worker(GlobalClock &gc, JobTable &jt, std::shared_ptr<Menu> m, std::string id = "DEFAULT_WID")
        : Person(id),
          gc_(gc),
          jt_(jt),
          menu_(m) {}

    /**
     * @description: move constructor.
     * @param w worker being moved
     */
    Worker(Worker &&);

    /**
     * @description: move assignment operator.
     * @param w worker being moved
     * @returns a reference to this worker.
     */
    Worker &operator=(Worker &&);

    /**
     * @description: destructor.
     */
    virtual ~Worker() = default;

    /**
     * @description: ensures that everything is prepared for run().
     */
    void init();

    /**
     * @description: the worker thread's main course of action.
     */
    void run();

    /**
     * @description: Splits on '-', returning the second half 
     * of this waiter's id.
     * @returns the numeric half of this waiter's id.
     */
    virtual const int getIDNumber() const;

    /**
     * @description: Accessor for the job table.
     * @returns a reference to the restaurant job table.
     */
    inline JobTable &getJobTable() { return jt_; }

    /**
     * @description: clock accessor.
     * @returns simulation clock reference.
     */
    inline GlobalClock &getClock() { return gc_; }

    /**
     * @description: thread accessor.
     * @returns the worker thread.
     */
    inline std::thread &getThread() { return t_; }

    /**
     * @description: pure virtual seating job handler. 
     * @param sj a seating job.
     */
    virtual void handleJob(SeatingJob &) = 0;

    /**
     * @description: pure virtual order job handler.
     * @param oj an order job.
     */
    virtual void handleJob(OrderJob &) = 0;

protected:
    GlobalClock &gc_;                        ///< simulation clock.
    JobTable &jt_;                           ///< simulation job table.
    std::shared_ptr<Menu> menu_;             ///< restaurant menu.
    std::vector<std::shared_ptr<Job>> jobs_; ///< worker's current jobs.
    std::thread t_;                          ///< worker thread.

private: ///< Workers are only moveable, not copyable.
    Worker(const Worker &) = delete;
    Worker &operator=(const Worker &) = delete;
};

/**
 * TODO once JobTable is being keyed on strings, remove getIDNumber().
 * TODO which getter methods actually make sense to have???
 */

#endif // WORKER_HPP