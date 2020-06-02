#include "Door.h"
#include "Foyer.h"
#include "Waiter.h"
#include <mutex>
#include <future>
#include <iostream>

Door::Door(Foyer &f) : comingIn_(),
                       goingOut_(),
                       mIn_(),
                       mOut_(),
                       foyer_(f)
{
    init();
}

Door::Door(const Door &d)
{
    if (this == &d)
        return;
    this->comingIn_ = d.comingIn_;
    this->goingOut_ = d.goingOut_;
    this->mIn_ = d.mIn_;
    this->mOut_ = d.mOut_;
    this->foyer_ = d.foyer_;
}

Door &Door::operator=(const Door &d)
{
    if (this == &d)
        return *this;
    this->comingIn_ = d.comingIn_;
    this->goingOut_ = d.goingOut_;
    this->mIn_ = d.mIn_;
    this->mOut_ = d.mOut_;
    this->foyer_ = d.foyer_;
}

void Door::init()
{
}

Waiter *Door::queueForService(Party *p)
{
    Waiter *w;
    { // begin critical section
        std::lock_guard<std::mutex> lg(foyer_.m_);
        int tID = foyer_.getNextTableID();
        foyer_.putParty(tID, p);
        /**
         * need a way to map TableIDs to Waiters HERE.
         * will assign all jobs to a single Waiter for now.
         */
        if (foyer_.waiters_->size() > 0)
            return (*foyer_.waiters_)[0];
        else
            return nullptr;
    } // end critical section
}