#ifndef WAITER_H
#define WAITER_H

#include "Person.h"
#include "Worker.h"
#include "Table.h"
#include "Foyer.h"
#include "JobTable.h"
#include "Job.h"
#include "OrderJob.h"
#include "SeatingJob.h"
#include <boost/signals2.hpp>
#include <string>
#include <vector>

/**
 * @class <code>Waiter</code>
 * @description: A restaurant waiter. Inherits from <code>Worker</code>.
 * @author ajm
 * @created: 2/19/20
 * @modified: 6/1/20
 */
class Waiter : public Worker
{
public:
    /**
     * @description: constructor.
     * @param id waiter id string.
     * @param fd waiter fd.
     * @param tables the tablespace.
     * @param foyer the foyer.
     * @param jt the job table.
     */
    Waiter(std::string, int, std::vector<Table> &, Foyer &, JobTable &);

    /**
     * @description: Used to seat Parties.
     * @param tID id of the Table where the Party shall be seated.
     * @param p Party to be seated.
     */
    void seatParty(unsigned, Party *);

    /**
     * @description: Accessor for foyer.
     */
    inline Foyer &getFoyer() { return foyer_; }

    /**
     * @description: Accessor for tablespace.
     */
    inline std::vector<Table> &getTablespace() { return tablespace_; }

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
     * @description: job handler method for SeatingJobs.
     * @param sj seating job that requires handling.
     */
    void handleJob(SeatingJob);

    /**
     * @description: job handler method for OrderJobs.
     * @param oj order job that requires handling.
     */
    void handleJob(OrderJob);

    /**
     * @description: ensures that everything is prepared for run().
     */
    void init();

    /**
     * @description: the waiter thread's main course of action.
     */
    void run();

private:
    std::string wID_;                ///< this waiter's unique id.
    std::vector<Table> &tablespace_; ///< where parties are seated.
    std::vector<Job> jobs_;          ///< the waiter's current jobs.
    Foyer &foyer_;                   ///< where Parties wait to be seated.
    JobTable &jobTable_;             ///< used to acquire jobs.
    std::condition_variable &cv_;    ///< this waiter's cv, pulled from the job table.
    mutable std::mutex &m_;          ///< this waiter's mutex, pulled from the job table.
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