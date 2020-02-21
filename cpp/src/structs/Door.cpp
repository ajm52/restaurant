#include "Door.h"

#include <iostream>

Door::Door() : comingIn_(),
               goingOut_(),
               mIn_(),
               mOut_(),
               entrySig_(),
               exitSig_(),
               entrySlot_(),
               exitSlot_()
{
    entrySig_.connect(entrySlot_);
    exitSig_.connect(exitSlot_);
}

void EntrySlot::operator()() const
{
    std::cout << "entered\n";
}

void ExitSlot::operator()() const
{
    std::cout << "left\n";
}