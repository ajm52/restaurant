#include "Foyer.hpp"
#include <iterator>
#include <map>
#include <mutex>

Foyer::Foyer(Foyer &&f)
    : toBeSeated_(std::move(f.toBeSeated_)), m_() {}

Foyer &Foyer::operator=(Foyer &&f)
{
    if (this == &f)
        return *this;
    toBeSeated_ = std::move(f.toBeSeated_);
    return *this;
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