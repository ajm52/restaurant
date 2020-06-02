#ifndef JOBTABLE_H
#define JOBTABLE_H

#include "Job.h"
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

/**
 * @class JobTable
 * @description: Communication interface used to
 * distribute jobs to restaurant workers.
 * How it works: 
 * - Workers wait on their own condition variable,
 * indexed by their own unique ID number.
 * - A notified Worker will check their queue for jobs,
 * indexed again by their own unique ID number.
 * 
 * @author ajm
 * @created: 5/29/20
 * @modified: 6/2/20
 */
class JobTable
{
public:
    /**
     * @description: constructor.
     * @param numWaiters # of restaurant waiters.
     */
    JobTable(unsigned);

    /**
     * @description: builds the job table.
     */
    void init();

    /**
     * @description: queues a job into the appropriate job list.
     * @param index used to identify the correct job queue.
     * @param job the job to be queued.
     */
    void queueJob(unsigned, Job *);

    /**
     * @description: acquires a job from a given job queue.
     * @param index the job list from which a job should be pulled.
     * @returns a pointer to the next job from a given job list. Returns
     * null if the job list is empty.
     */
    Job *acquireJob(unsigned);

    /**
     * @description: acquires all jobs from a given job queue.
     * @param the job list from which we shall pull from.
     * @returns a safe pointer to a list of pulled jobs. Returns
     * an empty list of there are no jobs to pull.
     */
    std::shared_ptr<std::vector<Job>> acquireAllJobs(unsigned);

    /**
     * @description: checks a given job flag to see if there is 
     * work to be done.
     * @param index points to a specific job flag.
     * @returns true if there is work to be done, false otherwise.
     */
    bool workToBeDone(unsigned);

    /**
     * @description: Accessor method for a given condition variable.
     * @param index points to a particular condition variable.
     * @returns a pointer to a given condition variable; returns nullptr
     * if the provided index is invalid.
     */
    std::condition_variable *getCV(unsigned);

    /**
     * @description: Accessor method for a given mutex.
     * @param index points to a particular mutex.
     * @returns a pointer to a given mutex; returns nullptr
     * if the provided index is invalid.
     */
    std::mutex *getMutex(unsigned);

private:
    unsigned numWaiters_;                         ///< # of restaurant waiters
    std::vector<std::condition_variable> cvList_; ///< worker CVs
    std::vector<std::queue<Job>> jobQueues_;      ///< worker job queues
    mutable std::vector<std::mutex> mList_;       ///< job queue mutexes
    std::vector<bool> jobFlags_;                  ///< job flags
};
#endif // JOBTABLE_H

/**
 * TODO write methods validateJobQueueSize(unsigned) and validateIndex(unsigned)
 * to eliminate repeated code.
 */
