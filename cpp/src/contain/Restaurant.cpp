#include "Restaurant.h"
#include "Waiter.h"
#include <vector>

void Restaurant::LoaderAccess::assignWaiters(Restaurant *r, std::vector<Waiter> &w)
{
    r->waiters_.clear();
    r->waiters_ = std::move(w);
}