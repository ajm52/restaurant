#ifndef JOB_HPP
#define JOB_HPP

#include "Worker.hpp"

/**
 * @struct Job
 * @author ajm
 * @description: represents a Job, which can 
 * take one of three forms: OrderJob, SeatingJob, or
 * CleaningJob.
 * 
 * An OrderJob will have an attached Order, 
 * and both SeatingJobs and CleaningJobs will 
 * have an attached Table ID.
 */
struct Job
{
    /**
     * @description: pure virtual handler method to be implemented 
     * by concrete Job structs.
     * @param w the worker responsible for the job.
     * 
     * NOTE We avoid pure virtual to simplify
     * generic usage in JobTable.
     */
    virtual void accept(Worker &w) = 0;
    virtual ~Job() = default;
};
#endif // JOB_HPP