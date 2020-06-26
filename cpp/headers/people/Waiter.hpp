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
     * @description: Splits on '-', returning the second half 
     * of this waiter's id.
     * @returns the numeric half of this waiter's id.
     */
    const int getIDNumber() const;

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

private:
    /**
     * user-defined containers.
     */
    std::vector<std::shared_ptr<Table>> &tablespace_; ///< where parties are seated.
    Foyer *foyer_;                                    ///< where Parties wait to be seated.

    Waiter(const Waiter &) = delete;
    Waiter &operator=(const Waiter &) = delete;
};

/**
 * 
 * TODO add access to Kitchen/Bar, both of which can by done by
 * implementing handleJob(OrderJob&).
 * TODO once JobTable is being keyed on strings, remove getIDNumber().
 * 
 */
#endif // WAITER_HPP