#include "Foyer.hpp"
#include <iterator>
#include <map>
#include <mutex>

void Foyer::putParty(unsigned id, std::shared_ptr<Party> pPtr)
{

    { // begin critical section
        std::lock_guard<std::mutex> lg(m_);
        toBeSeated_.insert(std::pair<unsigned, std::shared_ptr<Party>>(id, pPtr));
    } // end critical section
}

std::shared_ptr<Party> Foyer::removeParty(unsigned id)
{
    std::shared_ptr<Party> ret;
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