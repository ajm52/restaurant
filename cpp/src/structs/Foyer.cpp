#include "Foyer.h"
#include "Waiter.h"
#include "JobTable.h"
#include "SeatingJob.h"
#include <iterator>
#include <vector>
#include <map>
#include <mutex>

Foyer::Foyer()
    : tableCount_(0),
      nextTableIDs_(),
      toBeSeated_(),
      m_(),
      jobTable_() {}

Foyer::Foyer(unsigned tableCount, JobTable &jobTable)
    : tableCount_(tableCount),
      nextTableIDs_(),
      toBeSeated_(),
      m_(),
      jobTable_(jobTable)
{
    prepSeatingQueue();
}

Foyer::Foyer(const Foyer &f)
{
    if (this != &f)
    {
        this->tableCount_ = f.tableCount_;
        this->nextTableIDs_ = f.nextTableIDs_;
        this->toBeSeated_ = f.toBeSeated_;
        this->m_ = f.m_;
        this->jobTable_ = f.jobTable_;
    }
}

Foyer &Foyer::operator=(const Foyer &f)
{
    if (this == &f)
        return;
    this->tableCount_ = f.tableCount_;
    this->nextTableIDs_ = f.nextTableIDs_;
    this->toBeSeated_ = f.toBeSeated_;
    this->m_ = f.m_;
    this->jobTable_ = f.jobTable_;
    return *this;
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

bool Foyer::putParty(unsigned id, Party *pPtr)
{
    if (toBeSeated_.find(id) != toBeSeated_.end())
    {
        return false;
    }
    toBeSeated_.insert(std::pair<unsigned, Party *>(id, pPtr));
    SeatingJob *job = new SeatingJob(id);

    //TODO write a method that maps tIDs to wIDs.
    //for now, we assume only one waiter.

    unsigned wID = 1; //NOTE this is a magic constant!!!

    { // begin critical section
        std::lock_guard<std::mutex> lg(*jobTable_.getMutex(wID));
        jobTable_.queueJob(wID, job);
    } // end critical section
    return true;
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