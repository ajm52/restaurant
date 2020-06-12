#include "Foyer.hpp"
#include "Waiter.hpp"
#include <iterator>
#include <vector>
#include <map>
#include <mutex>

Foyer::Foyer()
    : tableCount_(0),
      nextTableIDs_(),
      toBeSeated_(),
      m_() {}

Foyer::Foyer(unsigned tableCount)
    : tableCount_(tableCount),
      nextTableIDs_(),
      toBeSeated_(),
      m_()
{
    prepSeatingQueue();
}

void Foyer::prepSeatingQueue()
{
    for (unsigned i = 1; i <= tableCount_; ++i)
        nextTableIDs_.push(i);
}

unsigned Foyer::getNextTableID()
{
    int id = nextTableIDs_.front();
    nextTableIDs_.pop();
    return id;
}

void Foyer::putParty(unsigned id, Party *pPtr)
{

    { // begin critical section
        std::lock_guard<std::mutex> lg(m_);
        toBeSeated_.insert(std::pair<unsigned, Party *>(id, pPtr));
    } // end critical section
}

Party *Foyer::removeParty(unsigned id)
{
    Party *ret = nullptr;
    { // begin critical section
        std::lock_guard<std::mutex> lg(m_);
        auto itr = toBeSeated_.find(id);
        if (itr != toBeSeated_.end())
        {
            ret = (*itr).second; //NOTE this might give us trouble...
            toBeSeated_.erase(id);
        }
    } // end critical section

    return ret;
}