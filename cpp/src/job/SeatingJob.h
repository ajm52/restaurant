#ifndef SEATINGJOB_H
#define SEATINGJOB_H

#include "Job.h"

class Waiter;

/**
 * @struct SeatingJob 
 * @description: A job to do with seating a Party.
 * @author ajm
 * @created: 5/29/20
 * @modified: 6/2/20
 */
struct SeatingJob : public Job
{
    /**
     * @description: constructor.
     * @param tID table ID where the party shall be seated.
     */
    SeatingJob(unsigned);

    unsigned tableID_; ///< used to index into Foyer's Party map.

    /**
     * @description: handler method used to 
     * complete this job.
     * @param w the waiter responsible for completing 
     * this job.
     */
    void handleJob(Waiter *);
};
#endif // SEATINGJOB_H