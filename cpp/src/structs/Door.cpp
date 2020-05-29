#include "Door.h"
#include "Foyer.h"
#include "Waiter.h"
#include <mutex>
#include <future>
#include <iostream>

Door::Door() : comingIn_(),
               goingOut_(),
               mIn_(),
               mOut_(),
               entrySig_(),
               exitSig_(),
               entrySlot_(),
               exitSlot_(),
               fd_(),
               foyer_()
{
    entrySig_.connect(entrySlot_);
    exitSig_.connect(exitSlot_);
}

void Door::signalEntry()
{
    Party *p;
    {
        std::lock_guard<std::mutex> lg(mIn_);
        p = comingIn_.front();
        if (p)
            comingIn_.pop();
    }
    entrySig_(&foyer_, p);
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

void EntrySlot::operator()(Foyer *f, Party *p)
{
    std::cout << "A party has entered the restaurant.\n";
    {
        std::lock_guard<std::mutex> lg(f->m_);
        f->putParty(0, p);     // will eventually need a method nextTableID().
        f->signalWaiter(0, 0); // will also need a way to map TableIDs to WaiterIDs.
    }
}

void ExitSlot::operator()()
{
    std::cout << "left\n";
}
