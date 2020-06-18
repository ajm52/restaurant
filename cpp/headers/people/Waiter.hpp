#ifndef WAITER_HPP
#define WAITER_HPP

#include "Worker.hpp"
#include "Table.hpp"
#include "GlobalClock.hpp"
#include "JobTable.hpp"
#include "Menu.hpp"
#include <string>
#include <vector>
#include <memory>
#include <thread>

struct Job;
struct OrderJob;
struct SeatingJob;
struct Foyer;

/**
 * @class Waiter
 * @description: A restaurant waiter. Inherits from Worker.
 * @author ajm
 */
class Waiter : public Worker
{
public:
    /**
     * @description: constructor.
     * @param id waiter id string.
     * @param gc simulation clock.
     * @param tables the tablespace.
     * @param foyer the foyer.
     * @param jt the job table.
     * @param menu the restaurant menu.
     */
    Waiter(std::string, GlobalClock &, std::vector<std::shared_ptr<Table>> &, Foyer &, JobTable &, std::shared_ptr<Menu>);

    /**
     * @description: copy constructor.
     * @param w waiter we're copying from.
     */
    Waiter(const Waiter &);

    /**
     * @description: copy assignment operator.
     * @param w waiter we're copying from.
     * @returns this as a copy of w.
     */
    Waiter &operator=(const Waiter &);

    /**
     * @description: move constructor.
     * @param w waiter we're moving.
     */
    Waiter(Waiter &&);

    /**
     * @description: move assignment operator.
     * @param w waiter we're moving.
     * @returns this with w's member data.
     */
    Waiter &operator=(Waiter &&);

    /**
     * @description: Accessor for foyer.
     * @returns a pointer to the foyer.
     */
    inline Foyer *getFoyer() { return foyer_; }

    /**
     * @description: Accessor for tablespace.
     * @returns the restaurant's tables.
     */
    inline std::vector<std::shared_ptr<Table>> &getTablespace() { return tablespace_; }

    /**
     * @description: Accessor for the job table.
     * @returns a reference to the restaurant job table.
     */
    inline JobTable &getJobTable() { return jobTable_; }

    /**
     * @description: Splits on '-', returning the second half 
     * of this waiter's id.
     * @returns the numeric half of this waiter's id.
     */
    const unsigned getIDNumber() const;

    /**
     * @description: ensures that everything is prepared for run().
     */
    void init();

    /**
     * @description: the waiter thread's main course of action.
     */
    void run();

    /**
     * @description: handler method used to 
     * complete this job.
     * @param sj seating job to be completed by this Waiter.
     */
    void handleJob(SeatingJob &);

    /**
     * @description: handler method used to 
     * complete this job.
     * @param oj order job to be completed by this Waiter.
     */
    void handleJob(OrderJob &);

    /**
     * @description: clock accessor.
     * @returns simulation clock reference.
     */
    inline GlobalClock &getClock() { return clock_; }

private:
    std::string wID_;    ///< this waiter's unique id.
    GlobalClock &clock_; ///< simulation clock.

    /**
     * user-defined containers.
     */
    std::vector<std::shared_ptr<Table>> &tablespace_; ///< where parties are seated.
    std::vector<std::shared_ptr<Job>> jobs_;          ///< the waiter's current jobs.
    Foyer *foyer_;                                    ///< where Parties wait to be seated.
    JobTable &jobTable_;                              ///< used to acquire jobs.
    std::shared_ptr<Menu> menu_;                      ///< the restaurant menu.

    std::thread mthread_; ///< the waiter thread.
};

//TODO change ordering of variables (cv and m at top)

/**
 * 
 * TODO
 * - add access to Kitchen.
 * - add access to Bar.
 */
#endif // WAITER_HPP