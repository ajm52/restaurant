#include "Door.h"
#include "Foyer.h"
#include <mutex>
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
    entrySlot_(foyer_, p);
}

void EntrySlot::operator()(Foyer f, Party *p)
{
    std::cout << "A party has entered the restaurant.\n";
    {
        std::lock_guard<std::mutex> lg(f.m_);
        f.putParty(0, p); // will eventually need a method nextTableID().
        }
}

void ExitSlot::operator()()
{
    std::cout << "left\n";
}