#include "Doorman.hpp"
#include "SeatingJob.hpp"
#include "GlobalClock.hpp"
#include "Party.hpp"
#include <thread>
#include <iostream>
#include <mutex>
#include <memory>

void Doorman::init()
{
    std::thread t1(&Doorman::controlInbound, this);
    // std::thread t2(&Doorman::controlOutbound, this);
    incomingHandler_ = std::move(t1);
}

void Doorman::controlInbound()
{
    std::cout << getClock() << " Doorman[I] awake.\n";

    while (true)
    {
        std::unique_lock<std::mutex> ul(d_.getEntryMutex());

        while (d_.getEntryQueue().empty()) // Doorman waits until it is notified by an inbound Party.
            d_.getCV().wait(ul);

        std::cout << getClock() << " Doorman[I]: Dealing with queued Parties..\n";

        // begin critical section; wait(ul) automatically locks on return.

        while (!d_.getEntryQueue().empty()) // transfer all queued Parties into the Foyer (or as many as possible until Restaurant hits cap)
        {
            std::shared_ptr<Party> p = d_.getEntryQueue().front();
            d_.getEntryQueue().pop();
            unsigned tID = f_.getNextTableID(); // place party in the foyer
            f_.putParty(tID, p);

            //TODO write a method that maps tIDs to wIDs.
            //for now, we assume only one waiter.

            unsigned wID = 0; //NOTE this is a magic constant

            std::shared_ptr<SeatingJob> jPtr = std::make_shared<SeatingJob>(tID);
            jt_.queueJob(wID, jPtr);

            jt_.getCV(wID)->notify_one(); // Notify Waiter that a Party is in the Foyer.

            std::cout << getClock() << " Doorman[I]: Notified W-" << std::to_string(wID) << "; " << p->getPID() << " is in the Foyer.\n";
        }

        ul.unlock(); // end critical section
    }
}

void Doorman::controlOutbound()
{
}