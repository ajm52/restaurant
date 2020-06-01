#include "Waiter.h"
#include "Table.h"
#include "Job.h"
#include "Party.h"
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
#include <memory>
#include <iostream>
#include <boost/algorithm/string.hpp>

Waiter::Waiter(std::string id, int fd, std::vector<Table> &tables, Foyer &foyer, JobTable &jt)
    : Worker(fd, id),
      tablespace_(tables),
      foyer_(foyer),
      jobTable_(jt)
{
    init();
}

void Waiter::seatParty(unsigned tID, Party *p)
{
    if (tID < tablespace_.size())
    {
        Table::WaiterAccess::setParty(&tablespace_[tID], p);
    }
}

const unsigned Waiter::getIDNumber() const
{
    std::vector<std::string> tokens;
    boost::algorithm::split(tokens, this->getId(), boost::is_any_of('-'));
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
    std::thread t(&Waiter::run, this);
    t.join();
}

void Waiter::run()
{
    while (true)
    {
        if (jobTable_.workToBeDone(this->getIDNumber()))
        {
            std::unique_lock<std::mutex> ul(this->m_);
            this->cv_.wait(ul, [this] {
                return this->getJobTable().workToBeDone(this->getIDNumber());
            });
            std::shared_ptr<std::vector<Job>> jobs = this->getJobTable().acquireAllJobs(this->getIDNumber());
            for (int i = 0; i < jobs.get()->size(); ++i)
            { // push all new jobs into current job vector.
                jobs_.push_back(jobs.get()->at(i));
            }
            for (int i = 0; i < jobs_.size(); ++i)
            {
                // call handleJob(Job) here.
            }
        }
        else
        {
            std::cout << this->getId() << " has no work, sleeping..\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    } // end main while loop
}