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
 * @created: 5/29/20
 * @modified: 6/3/20
 */
struct OrderJob : public Job
{
    OrderJob(Order o) : order_(o) {}
    void accept(Worker &w) { w.handleJob(this); }
    Order order_;
};
#endif // ORDERJOB_HPP