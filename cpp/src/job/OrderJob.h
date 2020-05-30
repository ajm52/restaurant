#ifndef ORDERJOB_H
#define ORDERJOB_H

#include "Job.h"
#include "Order.h"

/**
 * @struct OrderJob
 * @description: A job associated with
 * a restaurant order.
 * @author ajm
 * @created: 5/29/20
 * @modified: 5/29/20
 */
struct OrderJob : public Job
{
    Order order_;
};
#endif // ORDERJOB_H