#include "Waiter.hpp"
#include "GlobalClock.hpp"
#include "Table.hpp"
#include "Job.hpp"
#include "SeatingJob.hpp"
#include "OrderJob.hpp"
#include "Party.hpp"
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
#include <memory>
#include <iostream>
#include <boost/algorithm/string.hpp>

Waiter::Waiter(std::string id, GlobalClock &gc, std::vector<std::shared_ptr<Table>> &tables, Foyer &foyer, JobTable &jt, std::shared_ptr<Menu> menu)
    : Worker(id),
      clock_(gc),
      tablespace_(tables),
      foyer_(&foyer),
      jobTable_(jt),
      mthread_(),
      menu_(menu)
{
    init();
}

Waiter::Waiter(const Waiter &w)
    : Worker(w.id_),
      clock_(w.clock_),
      tablespace_(w.tablespace_),
      jobs_(w.jobs_),
      foyer_(w.foyer_),
      jobTable_(w.jobTable_),
      mthread_(),
      menu_(w.menu_) {}

Waiter &Waiter::operator=(const Waiter &w)
{
    if (this == &w)
        return *this;
    id_ = w.id_;
    clock_ = w.clock_;
    tablespace_ = w.tablespace_;
    jobs_ = w.jobs_;
    foyer_ = w.foyer_;
    jobTable_ = w.jobTable_;
    menu_ = w.menu_;
    return *this;
}

Waiter::Waiter(Waiter &&w)
    : wID_(w.wID_),
      clock_(w.clock_),
      tablespace_(w.tablespace_),
      jobs_(std::move(w.jobs_)),
      foyer_(w.foyer_),
      jobTable_(w.jobTable_),
      mthread_(std::move(w.mthread_)),
      menu_(std::move(w.menu_))
{
    w.foyer_ = nullptr;
}

const unsigned Waiter::getIDNumber() const
{
    std::vector<std::string> tokens;
    boost::algorithm::split(tokens, this->getId(), boost::algorithm::is_any_of("-"));
    if (tokens.size() >= 2)
    {
        return std::stoi(tokens[1]);
    }
    else
    {
        return 0;
    }
}

void Waiter::init()
{
    std::thread t(&Waiter::run, std::ref(*this));
    mthread_ = std::move(t);
}

void Waiter::run()
{
    std::cout << getClock() << " " << getId() << " is awake.\n";
    while (true)
    {

        std::unique_lock<std::mutex> ul(*getJobTable().getMutex(getIDNumber())); //begin critical section

        while (!getJobTable().workToBeDone(getIDNumber()))
        {
            getJobTable().getCV(getIDNumber())->wait(ul);
        }
        std::cout << getClock() << " " << getId() << ": Work to be done. Acquiring jobs...\n";
        std::shared_ptr<std::vector<std::shared_ptr<Job>>> jobs = this->getJobTable().acquireAllJobs(this->getIDNumber(), true);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        std::cout << getClock() << " " << getId() << ": Jobs acquired. Pushing to local job list... ";
        for (int i = 0; i < jobs.get()->size(); ++i)
            jobs_.push_back(jobs.get()->at(i));

        std::cout << " done.\n";
        ul.unlock(); // end critical section

        std::this_thread::sleep_for(std::chrono::milliseconds(750));
        for (int i = 0; i < jobs_.size(); ++i)
        {
            //TODO add an ID string to Job.
            std::cout << getClock() << " " << getId() << ": Beginning Job#" << std::to_string(i) << ".\n";
            jobs_[i]->accept(*this);
            std::cout << getClock() << " " << getId() << ": Job#" << std::to_string(i) << " done.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        //TODO find a clean way to junk completed Jobs from the local job list.

        std::cout << getClock() << " " << getId() << ": Local job wave completed.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    } // end main while loop
}

void Waiter::handleJob(SeatingJob &sj)
{
    std::cout << getClock() << " " << getId() << ": Handling SJ for Table " << sj.tableID_ << std::endl;
    Party *pPtr = foyer_->removeParty(sj.tableID_);

    Table::WaiterAccess::seatParty(tablespace_[sj.tableID_], pPtr);
    Party::WaiterAccess::setTable(pPtr, tablespace_[sj.tableID_]);
    Party::WaiterAccess::setWaiter(pPtr, std::make_shared<Waiter>(*this));
    Party::WaiterAccess::setMenu(pPtr, menu_);
    Party::WaiterAccess::signalServiceStarted(pPtr);

    std::cout << getClock() << " " << getId() << ": Notified " << pPtr->getPID() << " that service has started.\n";
}

void Waiter::handleJob(OrderJob &oj)
{
    std::cout << getClock() << " " << getId() << ": handling OJ for order " << oj.order_.getOrderId() << std::endl;
}