#include "Foyer.h"
#include "Waiter.h"
#include <iterator>
#include <vector>
#include <map>
#include <mutex>

Foyer::Foyer() : table_(), m_(), newPartySignals_(), waiters_() {}

void Foyer::signalWaiter(unsigned wid, unsigned tid)
{
    Waiter *w;
    if (waiters_)
    {
        w = (*waiters_)[wid];
        (*newPartySignals_[wid])(w, tid); // signal the appropriate Waiter by index.
    }
}

void Foyer::assignWaiters(std::vector<Waiter *> &waiters)
{
    waiters_ = &waiters;
}

void Foyer::initConnections()
{
    for (int i = 0; i < waiters_->size(); ++i)
    {
        std::shared_ptr<NewPartySignal> sPtr(new NewPartySignal());
        sPtr->connect((*waiters_)[i]->getSlot());
        newPartySignals_.push_back(sPtr);
    }
}

bool Foyer::putParty(int id, Party *pPtr)
{
    std::lock_guard<std::mutex> lg(m_); // lock before reading/modifying
    if (table_.find(id) != table_.end())
        return false;
    table_.insert(std::pair<int, Party *>(id, pPtr));
    return true;
}

Party *Foyer::removeParty(int id)
{
    Party *ret = nullptr;
    std::lock_guard<std::mutex> lg(m_); // lock before reading/modifying
    auto itr = table_.find(id);
    if (itr != table_.end())
    {
        ret = (*itr).second;
        table_.erase(id);
    }
    //unlock
    return ret;
}