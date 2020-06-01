#ifndef JOB_H
#define JOB_H

/**
 * @struct Job
 * @description: represents a Job, which can 
 * take one of three forms: OrderJob, SeatingJob, or
 * CleaningJob.
 * 
 * An OrderJob will have an attached Order, 
 * and both SeatingJobs and CleaningJobs will 
 * have an attached Table ID.
 * @author ajm
 * @created: 5/29/20
 * @modified: 5/29/20
 */
struct Job
{
    /**
     * @description: virtual handler method to be implemented 
     * by concrete Job structs.
     */
    virtual void handleJob() = 0;
};
#endif // JOB_H