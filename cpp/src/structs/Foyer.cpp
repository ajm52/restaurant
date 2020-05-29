#include "Foyer.h"
#include "Waiter.h"
#include <iterator>
#include <vector>
#include <map>
#include <mutex>

Foyer::Foyer(int tableCount)
    : tableCount_(tableCount),
      readyForSeating_(),
      toBeSeated_(),
      m_(),
      newPartySignals_(),
      waiters_()
{
    prepSeatingQueue();
}

void Foyer::prepSeatingQueue()
{
    for (unsigned i = 1; i <= tableCount_; ++i)
        readyForSeating_.push(i);
}

int Foyer::getNextTableID()
{
    int id = readyForSeating_.front();
    readyForSeating_.pop();
    return id;
}

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
    if (toBeSeated_.find(id) != toBeSeated_.end())
        return false;
    toBeSeated_.insert(std::pair<int, Party *>(id, pPtr));
    return true;
}

Party *Foyer::removeParty(int id)
{
    Party *ret = nullptr;
    std::lock_guard<std::mutex> lg(m_); // lock before reading/modifying
    auto itr = toBeSeated_.find(id);
    if (itr != toBeSeated_.end())
    {
        ret = (*itr).second;
        toBeSeated_.erase(id);
    }
    //unlock
    return ret;
}