#include "SeatingJob.h"
#include "Waiter.h"
#include <iostream>

SeatingJob::SeatingJob(unsigned tID)
    : tableID_(tID) {}

void SeatingJob::handleJob(Waiter *w)
{
    if (w)
        std::cout << w.getId() << " has begun SeatingJob for table " << this->tableID_ << std::endl;
}