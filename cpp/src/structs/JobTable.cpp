#include "JobTable.hpp"
#include "Job.hpp"
#include <vector>
#include <mutex>
#include <memory>
#include <queue>
#include <condition_variable>
#include <exception>
#include <iostream>

JobTable::JobTable(unsigned numWaiters)
    : numWaiters_(numWaiters),
      cvMap_(),
      jobQueues_(numWaiters_),
      mMap_(),
      jobFlags_(numWaiters_, false) {}

void JobTable::queueJob(unsigned index, Job *job)
{
    if (index >= numWaiters_) //TODO throw an exception here.
        return;
    { //begin critical section
        std::lock_guard<std::mutex> lg(*(mMap_[index]));
        jobQueues_[index].push(job);
    } //end critical section
    //(*cvList_)[index]->notify_one();
}

Job *JobTable::acquireJob(unsigned index)
{
    if (index >= numWaiters_ || jobQueues_[index].size() == 0) //TODO throw an exception here.
        return nullptr;
    Job *job;
    { //begin critical section
        std::lock_guard<std::mutex> lg(*(mMap_[index]));
        job = jobQueues_[index].front();
        jobQueues_[index].pop();
    } //end critical section
    return job;
}

std::shared_ptr<std::vector<Job *>> JobTable::acquireAllJobs(unsigned index)
{
    std::vector<Job *> jobs;
    if (index < numWaiters_ && jobQueues_[index].size() > 0)
    {
        { //begin critical section
            std::lock_guard<std::mutex> lg(*(mMap_[index]));
            while (!jobQueues_[index].empty())
            {
                Job *j = jobQueues_[index].front();
                jobQueues_[index].pop();
                jobs.push_back(j);
            }
        } //end critical section
    }
    return std::make_shared<std::vector<Job *>>(jobs);
}

bool JobTable::workToBeDone(unsigned index)
{
    if (index < jobQueues_.size() && !jobQueues_[index].empty())
    {
        return true;
    }
    return false;
}

std::shared_ptr<std::condition_variable> JobTable::getCV(unsigned index)
{
    std::cout << std::to_string(index) << ", "
              << std::to_string(numWaiters_) << "\n";
    assert(index <= numWaiters_);
    return cvMap_[index];
}

std::shared_ptr<std::mutex> JobTable::getMutex(unsigned index)
{
    assert(index <= numWaiters_);
    return mMap_[index];
}