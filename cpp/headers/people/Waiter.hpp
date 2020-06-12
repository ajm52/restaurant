#ifndef WAITER_HPP
#define WAITER_HPP

#include "Worker.hpp"
#include "Table.hpp"
#include "JobTable.hpp"
#include <string>
#include <vector>
#include <memory>

struct Job;
struct OrderJob;
struct SeatingJob;
struct Foyer;

/**
 * @class <code>Waiter</code>
 * @description: A restaurant waiter. Inherits from <code>Worker</code>.
 * @author ajm
 * @created: 2/19/20
 * @modified: 6/3/20
 */
class Waiter : public Worker
{
public:
    /**
     * @description: constructor.
     * @param id waiter id string.
     * @param tables the tablespace.
     * @param foyer the foyer.
     * @param jt the job table.
     */
    Waiter(std::string, std::vector<std::shared_ptr<Table>> &, Foyer &, JobTable &);

    Waiter(Waiter &&);

    Waiter &operator=(Waiter &&);

    /**
     * @description: Used to seat Parties.
     * @param tID id of the Table where the Party shall be seated.
     * @param p Party to be seated.
     */
    void seatParty(unsigned, Party *);

    /**
     * @description: Accessor for foyer.
     */
    inline Foyer *getFoyer() { return foyer_; }

    /**
     * @description: Accessor for tablespace.
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

    void allocateService(Party *, unsigned);

    /**
     * @description: handler method used to 
     * complete this job.
     * @param sj seating job to be completed by this Waiter.
     */
    void handleJob(SeatingJob *);

    /**
     * @description: handler method used to 
     * complete this job.
     * @param oj order job to be completed by this Waiter.
     */
    void handleJob(OrderJob *);

private:
    std::string wID_;                                 ///< this waiter's unique id.
    std::vector<std::shared_ptr<Table>> &tablespace_; ///< where parties are seated.
    std::vector<Job *> jobs_;                         ///< the waiter's current jobs.
    Foyer *foyer_;                                    ///< where Parties wait to be seated.
    JobTable &jobTable_;                              ///< used to acquire jobs.
    std::condition_variable &cv_;                     ///< this waiter's cv, pulled from the job table.
    std::mutex &m_;                                   ///< this waiter's mutex, pulled from the job table.

    Waiter(const Waiter &) = delete;
    Waiter &operator=(const Waiter &) = delete;
};

//TODO change ordering of variables (cv and m at top)
//TODO swap raw ptrs with smart ptrs

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
#endif // WAITER_HPP