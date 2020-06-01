#include "SeatingJob.h"
#include "Waiter.h"
#include <iostream>

void SeatingJob::handleJob(Waiter &w)
{
    std::cout << w.getId() << " has begun SeatingJob for table " << this->tableID_ << std::endl;
}