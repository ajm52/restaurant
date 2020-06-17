#ifndef ORDERJOB_HPP
#define ORDERJOB_HPP

#include "Job.hpp"
#include "Order.hpp"
#include "Worker.hpp"

/**
 * @struct OrderJob
 * @description: A job associated with
 * a restaurant order.
 * @author ajm
 */
struct OrderJob : public Job
{
    /**
     * @description: constructor
     * @param o the associated order.
     */
    OrderJob(Order o) : order_(o) {}

    /**
     * @description: takes advantage of runtime type information to call the correct handler method.
     * @param w the worker handling this job.
     */
    void accept(Worker &w) { w.handleJob(*this); }

    Order order_; ///< the associated order.
};
#endif // ORDERJOB_HPP