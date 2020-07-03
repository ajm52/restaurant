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
class Waiter : public Worker, public std::enable_shared_from_this<Waiter>
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
    Waiter(std::string, GlobalClock &, std::vector<std::shared_ptr<Table>> &, Foyer &, JobTable &, Menu &);

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

    Waiter(const Waiter &) = delete; ///< Waiter is neither copyable nor movable.
    Waiter &operator=(const Waiter &) = delete;
    Waiter(Waiter &&) = delete;
    Waiter &operator=(Waiter &&) = delete;

private:
    std::vector<std::shared_ptr<Table>> &tablespace_; ///< where parties are seated.
    Foyer &foyer_;                                    ///< where Parties wait to be seated.
};

/**
 * TODO add access to Kitchen/Bar, both of which can by done by
 * implementing handleJob(OrderJob&).
 */
#endif // WAITER_HPP