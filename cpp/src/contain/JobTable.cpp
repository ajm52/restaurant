#include "JobTable.hpp"
#include "Job.hpp"
#include <vector>
#include <mutex>
#include <memory>
#include <queue>
#include <condition_variable>
#include <exception>
#include <map>
#include <iostream>

JobTable::JobTable(unsigned numWaiters)
    : numWaiters_(numWaiters),
      cvMap_(),
      jobQueues_(numWaiters_),
      mMap_(),
      jobFlags_(numWaiters_, false)
{
    buildMaps();
}

JobTable::JobTable(const JobTable &jt)
    : numWaiters_(jt.numWaiters_),
      cvMap_(jt.cvMap_),
      jobQueues_(jt.jobQueues_),
      mMap_(jt.mMap_),
      jobFlags_(jt.jobFlags_) {}

JobTable &JobTable::operator=(const JobTable &jt)
{
    if (this == &jt)
        return *this;
    numWaiters_ = jt.numWaiters_;
    cvMap_ = jt.cvMap_;
    jobQueues_ = jt.jobQueues_;
    mMap_ = jt.mMap_;
    jobFlags_ = jt.jobFlags_;
    return *this;
}

JobTable::~JobTable()
{
    mMap_.clear();
    cvMap_.clear();
    jobQueues_.clear();
    jobFlags_.clear();
}

void JobTable::queueJob(unsigned index, std::shared_ptr<Job> job)
{
    if (index >= numWaiters_) //TODO throw an exception here.
        return;
    { //begin critical section
        std::cout << "lock\n";
        std::lock_guard<std::mutex> lg(*(mMap_[index]));
        std::cout << "lock\n";
        jobQueues_[index].push(job);
        std::cout << "lock\n";
        jobFlags_[index] = true;
    } //end critical section

    std::cout << "job queued\n";
}

std::shared_ptr<Job> JobTable::acquireJob(unsigned index, bool isLocked)
{
    assert(index < numWaiters_ && jobQueues_[index].size() > 0);
    std::shared_ptr<Job> job;
    if (isLocked)
    {
        job = jobQueues_[index].front();
        jobQueues_[index].pop();
    }
    else
    {
        { //begin critical section
            std::lock_guard<std::mutex> lg(*(mMap_[index]));
            job = jobQueues_[index].front();
            jobQueues_[index].pop();
        } //end critical section
    }

    return job;
}

std::shared_ptr<std::vector<std::shared_ptr<Job>>> JobTable::acquireAllJobs(unsigned index, bool isLocked)
{
    assert(index < numWaiters_ && jobQueues_[index].size() > 0);
    std::vector<std::shared_ptr<Job>> jobs;
    if (isLocked)
    { //NOTE put repeated code into a single private method!!
        while (!jobQueues_[index].empty())
        {
            std::shared_ptr<Job> job = jobQueues_[index].front();
            jobQueues_[index].pop();
            jobs.push_back(job);
        }
        jobFlags_[index] = false;
    }
    else
    {
        { //begin critical section
            std::lock_guard<std::mutex> lg(*(mMap_[index]));
            while (!jobQueues_[index].empty())
            {
                std::shared_ptr<Job> job = jobQueues_[index].front();
                jobQueues_[index].pop();
                jobs.push_back(job);
            }
            jobFlags_[index] = false;
        } //end critical section
    }
    return std::make_shared<std::vector<std::shared_ptr<Job>>>(jobs);
}

bool JobTable::workToBeDone(unsigned index)
{
    return index < jobQueues_.size() && !jobQueues_[index].empty();
}

std::shared_ptr<std::condition_variable> JobTable::getCV(unsigned index)
{
    assert(index < numWaiters_);
    return cvMap_[index];
}

std::shared_ptr<std::mutex> JobTable::getMutex(unsigned index)
{
    assert(index < numWaiters_);
    return mMap_[index];
}

void JobTable::buildMaps()
{
    for (int i = 0; i < numWaiters_; ++i)
    {
        cvMap_.emplace(i, std::make_shared<std::condition_variable>());
        mMap_.emplace(i, std::make_shared<std::mutex>());
    }
}