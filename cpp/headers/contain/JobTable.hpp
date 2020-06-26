#ifndef JOBTABLE_HPP
#define JOBTABLE_HPP

#include "Job.hpp"
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <map>

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
    ~JobTable();

    /**
     * @description: queues a job into the appropriate job list.
     * @param index used to identify the correct job queue.
     * @param job the job to be queued.
     */
    void queueJob(unsigned, std::shared_ptr<Job>);

    /**
     * @description: acquires a job from a given job queue.
     * @param index the job list from which a job should be pulled.
     * @param isLocked whether or not the mutex has already been locked.
     * @returns a pointer to the next job from a given job list. Returns
     * null if the job list is empty.
     */
    std::shared_ptr<Job> acquireJob(unsigned, bool);

    /**
     * @description: acquires all jobs from a given job queue.
     * @param the job list from which we shall pull from.
     * @param isLocked whether or not the mutex has already been locked.
     * @returns a safe pointer to a list of pulled jobs. Returns
     * an empty list of there are no jobs to pull.
     */
    std::shared_ptr<std::vector<std::shared_ptr<Job>>> acquireAllJobs(unsigned, bool);

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
    std::shared_ptr<std::condition_variable> getCV(unsigned);

    /**
     * @description: Accessor method for a given mutex.
     * @param index points to a particular mutex.
     * @returns a pointer to a given mutex; returns nullptr
     * if the provided index is invalid.
     */
    std::shared_ptr<std::mutex> getMutex(unsigned);

    /**
     * @description: waiter count accessor.
     * @returns the # of waiters in the restaurant.
     */
    inline const unsigned waiterCount() const { return numWaiters_; }

    /**
     * @description: cook count accessor.
     * @returns the # of cooks in the restaurant.
     */
    inline const unsigned cookCount() const { return numCooks_; }

    /**
     * @description: bartender count accessor.
     * @returns the # of bartenders in the restaurant.
     */
    inline const unsigned bartenderCount() const { return numBartenders_; }

private:
    unsigned numWaiters_;                                                ///< # of restaurant waiters
    unsigned numCooks_;                                                  ///< # of restaurant cooks
    unsigned numBartenders_;                                             ///< # of restaurant bartenders
    std::map<unsigned, std::shared_ptr<std::condition_variable>> cvMap_; ///< worker CVs
    std::vector<std::queue<std::shared_ptr<Job>>> jobQueues_;            ///< worker job queues
    std::map<unsigned, std::shared_ptr<std::mutex>> mMap_;               ///< job queue mutexes
    std::vector<bool> jobFlags_;                                         ///< job flags

    /**
     * @description: map initializer function.
     * Call once at the beginning of simulation.
     */
    void buildMaps();
};
#endif // JOBTABLE_HPP

/**
 * TODO write methods validateJobQueueSize(unsigned) and validateIndex(unsigned)
 * to eliminate repeated code.
 * TODO make JobTable uncopyable, yet moveable.
 * TODO eliminate the need for worker tallies; use strings as map keys instead.
 */
