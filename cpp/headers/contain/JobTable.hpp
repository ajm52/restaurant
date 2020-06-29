#ifndef JOBTABLE_HPP
#define JOBTABLE_HPP

#include "WorkerJobData.hpp"
#include <vector>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <map>

struct Job;

/**
 * @class JobTable
 * @description: Communication interface used to
 * distribute jobs to restaurant workers.
 * How it works: 
 * - Workers wait on their own condition variable,
 * indexed by their own unique ID number.
 * - A notified Worker will check their queue for jobs,
 * indexed again by their own unique ID number.
 * @author ajm
 */
class JobTable
{
public:
    /**
     * @description: constructor.
     * @param numWaiters # of restaurant waiters
     * @param numCooks # of restaurant cooks
     * @param numBartenders # of restaurant bartenders
     */
    JobTable(unsigned = 0, unsigned = 0, unsigned = 0);

    /**
     * @description: copy constructor.
     * @param jt jobtable we're copying
     */
    JobTable(const JobTable &);

    /**
     * @description: copy assignment operator.
     * @param jt jobtable we're copying
     * @returns a reference to this jobtable.
     */
    JobTable &operator=(const JobTable &);

    /**
     * @description: destructor.
     */
    ~JobTable() = default;

    /**
     * @description: queues a job into the appropriate job list.
     * @param key worker id string.
     * @param job the job to be queued.
     */
    void queueJob(std::string, std::shared_ptr<Job>);

    /**
     * @description: acquires all jobs from a given job queue.
     * @param key worker id string.
     * @param isLocked whether or not the mutex has already been locked.
     * @returns a safe pointer to a list of pulled jobs. Returns
     * an empty list of there are no jobs to pull.
     */
    std::shared_ptr<std::vector<std::shared_ptr<Job>>> acquireJobs(std::string, bool);

    /**
     * @description: checks a given job flag to see if there is 
     * work to be done.
     * @param key worker id string.
     * @returns true if there is work to be done, false otherwise.
     */
    bool workToBeDone(std::string);

    /**
     * @description: Accessor method for a given condition variable.
     * @param key worker id string.
     * @returns a pointer to a given condition variable; returns nullptr
     * if the provided index is invalid.
     */
    std::condition_variable &getCV(std::string);

    /**
     * @description: Accessor method for a given mutex.
     * @param key worker id string.
     * @returns a pointer to a given mutex; returns nullptr
     * if the provided index is invalid.
     */
    std::mutex &getMutex(std::string);

private:
    mutable std::map<std::string, std::shared_ptr<WorkerJobData>> dataMap_; ///< worker data map; contains CVs, mutices, job queues, and flags.

    /**
     * @description: map initializer function.
     * @param numWaiters # of restaurant waiters
     * @param numCooks # of restaurant cooks
     * @param numBartenders # of restaurant bartenders
     */
    void buildMap(unsigned = 0, unsigned = 0, unsigned = 0);

    /**
     * @description: map key validator.
     * @param key worker id string.
     * @returns true if key-value mapping exists, false otherwise.
     */
    bool validateKey(std::string);
};
#endif // JOBTABLE_HPP

/**
 * TODO make JobTable uncopyable, yet moveable.
 */
