#include "JobTable.hpp"
#include "Job.hpp"
#include "WorkerJobData.hpp"
#include <vector>
#include <mutex>
#include <memory>
#include <queue>
#include <condition_variable>
#include <exception>
#include <map>
#include <iostream>

JobTable::JobTable(unsigned numWaiters, unsigned numCooks, unsigned numBartenders)
    : dataMap_()
{
    buildMap(numWaiters, numCooks, numBartenders);
}

void JobTable::queueJob(std::string key, std::shared_ptr<Job> job)
{
    if (!validateKey(key)) //TODO throw an exception here.
        return;
    { //begin critical section
        std::lock_guard<std::mutex> lg(dataMap_[key]->m_);
        dataMap_[key]->jobs_.push(job);
        dataMap_[key]->workToBeDone_ = true;
        dataMap_[key]->cv_.notify_one();
    } //end critical section
}

std::shared_ptr<std::vector<std::shared_ptr<Job>>> JobTable::acquireJobs(std::string key, bool isLocked)
{
    assert(validateKey(key)); //TODO throw an exception here.

    std::vector<std::shared_ptr<Job>> jobs;
    //ANCHOR investigate typedef for this ^^^

    std::unique_lock<std::mutex> ul(dataMap_[key]->m_, std::defer_lock);
    //ANCHOR investigate typedef for this ^^^

    if (!isLocked) // if m isn't locked pre-function call, lock now.
        ul.lock();

    while (!dataMap_[key]->jobs_.empty())
    {
        std::shared_ptr<Job> job = dataMap_[key]->jobs_.front();
        dataMap_[key]->jobs_.pop();
        jobs.push_back(job);
    }
    dataMap_[key]->workToBeDone_ = false;

    return std::make_shared<std::vector<std::shared_ptr<Job>>>(jobs);
    //ANCHOR investigate typedef for this ^^^
}

const bool JobTable::workToBeDone(std::string key) const
{

    return validateKey(key) && dataMap_[key]->workToBeDone_;
}

std::condition_variable &JobTable::getCV(std::string key) const
{
    assert(validateKey(key));
    return dataMap_[key]->cv_;
}

std::mutex &JobTable::getMutex(std::string key) const
{
    assert(validateKey(key));
    return dataMap_[key]->m_;
}

void JobTable::buildMap(unsigned numWaiters, unsigned numCooks, unsigned numBartenders)
{
    std::string key = "W-";
    for (int i = 0; i < numWaiters; ++i)
    {
        dataMap_.emplace(key + std::to_string(i), std::make_shared<WorkerJobData>());
    }
    key = "C-";
    for (int i = 0; i < numCooks; ++i)
    {
        dataMap_.emplace(key + std::to_string(i), std::make_shared<WorkerJobData>());
    }
    key = "B-";
    for (int i = 0; i < numBartenders; ++i)
    {
        dataMap_.emplace(key + std::to_string(i), std::make_shared<WorkerJobData>());
    }
}

const bool JobTable::validateKey(std::string key) const
{
    return dataMap_.find(key) != dataMap_.end();
}