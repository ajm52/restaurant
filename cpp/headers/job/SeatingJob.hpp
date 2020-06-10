#ifndef SEATINGJOB_HPP
#define SEATINGJOB_HPP

#include "Job.hpp"
#include "Worker.hpp"

/**
 * @struct SeatingJob 
 * @description: A job to do with seating a Party.
 * @author ajm
 * @created: 5/29/20
 * @modified: 6/3/20
 */
struct SeatingJob : public Job
{
    /**
     * @description: constructor.
     * @param tID table ID where the party shall be seated.
     */
    SeatingJob(unsigned tID) : tableID_(tID) {}
    void accept(Worker &w) { w.handleJob(this); }
    unsigned tableID_; ///< used to index into Foyer's Party map.
};
#endif // SEATINGJOB_HPP