#ifndef ORDERJOB_H
#define ORDERJOB_H

#include "Job.h"
#include "Order.h"
#include "Waiter.h"

/**
 * @struct OrderJob
 * @description: A job associated with
 * a restaurant order.
 * @author ajm
 * @created: 5/29/20
 * @modified: 6/1/20
 */
struct OrderJob : public Job
{
    Order order_;

    /**
     * @description: handler method used to 
     * complete this job.
     * @param w the waiter responsible for completing 
     * this job.
     */
    void handleJob(Waiter &);
};
#endif // ORDERJOB_H