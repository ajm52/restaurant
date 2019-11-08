#ifndef JOB_TABLE_H
#define JOB_TABLE_H

#include "job.h"
#include <map>
#include <queue>

/**
 * A map that holds mappings for all tables currently being waited on.
 * A mapping is defined as the following: (table_id, job).
 * 
 * Given that door's slot callables are the only things that will insert
 * into the job table, we will hold off on including a mutex (for now).
 * 
 * Good system design should avoid race conditions,
 * given that servers only read from the job_table upon reading a 
 * particular message from their socket, which the door callable
 * only writes to AFTER the table has been altered.
 * 
 * We include a queue to hold IDs of tables that have been
 * recently cleared as a way of load balancing.
 **/

struct job_table
{
    std::map<const std::uint32_t &, const job &> jobs_;
    std::queue<const std::uint32_t &> q_;
    explicit job_table::job_table() : jobs_(), q_() {}
    inline bool job_table::put(const std::uint32_t &key, const job &value)
    {
        if (&jobs_[key] != NULL)
            return false;
        jobs_.insert(std::pair<const std::uint32_t &, const job &>(key, value));
        return true;
    }
    inline void job_table::remove(const std::uint32_t &key)
    {
        if (&jobs_[key] == NULL)
            return;
        q_.push(key);
        jobs_.erase(key);
    }
};

#endif // JOB_TABLE_H