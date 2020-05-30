#ifndef SEATINGJOB_H
#define SEATINGJOB_H

#include "Job.h"

/**
 * @struct SeatingJob 
 * @description: A job to do with seating a Party.
 * @author ajm
 * @created: 5/29/20
 * @modified: 5/29/20
 */
struct SeatingJob : public Job
{
    unsigned tableID_; ///< used to index into Foyer's Party map.
};
#endif // SEATINGJOB_H