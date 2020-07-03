#ifndef ORDERJOB_HPP
#define ORDERJOB_HPP

#include "Job.hpp"
#include "Order.hpp"
#include "Worker.hpp"
#include <memory>

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
    OrderJob(std::shared_ptr<Order> o) : order_(o) {}

    /**
     * @description: takes advantage of runtime type information to call the correct handler method.
     * @param w the worker handling this job.
     */
    void accept(Worker &w) { w.handleJob(*this); }

    std::shared_ptr<Order> order_; ///< the associated order.
};
#endif // ORDERJOB_HPP