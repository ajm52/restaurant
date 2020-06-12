#include "Doorman.hpp"
#include "SeatingJob.hpp"
#include <thread>
#include <iostream>
#include <mutex>

void Doorman::init()
{
    // std::thread t1(&Doorman::controlInbound, this);
    // std::thread t2(&Doorman::controlOutbound, this);
    // t1.detach();
    // t2.detach();
}

void Doorman::controlInbound()
{
    while (true)
    {
        std::unique_lock<std::mutex> ul(d_.getEntryMutex(), std::defer_lock);
        do
        {
            d_.getCV().wait(ul);
        } while (d_.getEntryQueue().empty());
        std::cout << "inbound notification!\n";
        ul.lock();
        while (!d_.getEntryQueue().empty())
        {
            std::shared_ptr<Party> p = d_.getEntryQueue().front();
            d_.getEntryQueue().pop();

            unsigned tID = f_.getNextTableID(); // place party in the foyer
            //f_.putParty(tID, p);

            //TODO write a method that maps tIDs to wIDs.
            //for now, we assume only one waiter.

            unsigned wID = 1;                      //NOTE this is a magic constant
            SeatingJob *job = new SeatingJob(tID); // place the corresponding SeatingJob in JobTable

            { // begin critical section
                std::lock_guard<std::mutex> lg(*jt_.getMutex(wID));
                jt_.queueJob(wID, job);
            } // end critical section

            // Notify Waiter
            jt_.getCV(wID)->notify_one();
        }
        ul.unlock();
    }
}

void Doorman::controlOutbound()
{
}

void Door::DoormanAccess::waitForOutbound(Door *d)
{
    std::unique_lock<std::mutex> ul(d->getExitMutex(), std::defer_lock);
    d->getCV().wait(ul, [d] { return !d->getExitQueue().empty(); });
}