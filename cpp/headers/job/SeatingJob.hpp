#ifndef SEATINGJOB_HPP
#define SEATINGJOB_HPP

#include "Job.hpp"
#include "Worker.hpp"

/**
 * @struct SeatingJob 
 * @description: A job to do with seating a Party.
 * @author ajm
 */
struct SeatingJob : public Job
{
    /**
     * @description: constructor.
     * @param tID table ID where the party shall be seated.
     */
    SeatingJob(unsigned tID) : tableID_(tID) {}

    /**
     * @description: takes advantage of runtime type information to call the correct handler method.
     * @param w the worker handling this job.
     */
    void accept(Worker &w) { w.handleJob(*this); }

    unsigned tableID_; ///< used to index into Foyer's Party map.
};
#endif // SEATINGJOB_HPP