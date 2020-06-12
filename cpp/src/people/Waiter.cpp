#include "Waiter.hpp"
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

Waiter::Waiter(std::string id, std::vector<std::shared_ptr<Table>> &tables, Foyer &foyer, JobTable &jt)
    : Worker(id),
      tablespace_(tables),
      foyer_(&foyer),
      jobTable_(jt),
      cv_(*getJobTable().getCV(getIDNumber())),
      m_(*getJobTable().getMutex(getIDNumber()))
{
    init();
}

Waiter::Waiter(Waiter &&w)
    : wID_(w.wID_),
      tablespace_(w.tablespace_),
      jobs_(std::move(w.jobs_)),
      foyer_(w.foyer_),
      jobTable_(w.jobTable_),
      cv_(*jobTable_.getCV(getIDNumber())),
      m_(*jobTable_.getMutex(getIDNumber()))
{
    w.foyer_ = nullptr;
}

void Waiter::seatParty(unsigned tID, Party *p)
{
    if (tID < tablespace_.size())
    {
        //Table::WaiterAccess::setParty(tablespace_[tID], p);
    }
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
    // std::thread t(&Waiter::run, this);
    // t.detach();
}

void Waiter::run()
{
    while (true)
    {
        if (jobTable_.workToBeDone(this->getIDNumber()))
        {
            std::unique_lock<std::mutex> ul(this->m_); //begin critical section
            cv_.wait(ul, [this] {
                return this->getJobTable().workToBeDone(this->getIDNumber());
            });
            std::shared_ptr<std::vector<Job *>> jobs = this->getJobTable().acquireAllJobs(this->getIDNumber());
            for (int i = 0; i < jobs.get()->size(); ++i)
            { // push all new jobs into current job vector.
                jobs_.push_back(jobs.get()->at(i));
            }
            ul.unlock(); // end critical section

            for (int i = 0; i < jobs_.size(); ++i)
            {
                jobs_[i]->accept(*this);
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }
        else
        {
            std::cout << this->getId() << " has no work, sleeping..\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    } // end main while loop
}

void Waiter::allocateService(Party *p, unsigned tID)
{
    if (tID >= getTablespace().size()) //TODO throw exception here.
        return;

    // Party::WaiterAccess::setTable(p, &(getTablespace()[tID]));
    // Party::WaiterAccess::setWaiter(p, this);
    //Party::WaiterAccess::setMenu
    //Party::WaiterAccess::signalServiceStarted(p);
}

void Waiter::handleJob(SeatingJob *sj)
{
    std::cout << "handling SJ for table " << sj->tableID_ << std::endl;
}

void Waiter::handleJob(OrderJob *oj)
{
    std::cout << "handling OJ for order " << oj->order_.getOrderId() << std::endl;
}