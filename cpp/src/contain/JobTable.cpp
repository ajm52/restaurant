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

JobTable::JobTable(unsigned numWaiters, unsigned numCooks, unsigned numBartenders)
    : dataMap_()
{
    buildMap(numWaiters, numCooks, numBartenders);
}

JobTable::JobTable(const JobTable &jt)
    : dataMap_(jt.dataMap_) {}

JobTable &JobTable::operator=(const JobTable &jt)
{
    if (this == &jt)
        return *this;
    dataMap_ = jt.dataMap_;
    return *this;
}

void JobTable::queueJob(std::string key, std::shared_ptr<Job> job)
{
    if (!validateKey(key)) //TODO throw an exception here.
        return;
    { //begin critical section
        std::lock_guard<std::mutex> lg(dataMap_[key]->m_);
        dataMap_[key]->jobs_.push(job);
        dataMap_[key]->workToBeDone_ = true;
    } //end critical section
}

std::shared_ptr<std::vector<std::shared_ptr<Job>>> JobTable::acquireJobs(std::string key, bool isLocked)
{
    if (!validateKey(key)) //TODO throw an exception here.
        return;
    std::vector<std::shared_ptr<Job>> jobs;
    if (isLocked)
    { //NOTE put repeated code into a single private method!!
        while (!dataMap_[key]->jobs_.empty())
        {
            std::shared_ptr<Job> job = dataMap_[key]->jobs_.front();
            dataMap_[key]->jobs_.pop();
            jobs.push_back(job);
        }
        dataMap_[key]->workToBeDone_ = false;
    }
    else
    {
        { //begin critical section
            std::lock_guard<std::mutex> lg(dataMap_[key]->m_);
            while (!dataMap_[key]->jobs_.empty())
            {
                std::shared_ptr<Job> job = dataMap_[key]->jobs_.front();
                dataMap_[key]->jobs_.pop();
                jobs.push_back(job);
            }
            dataMap_[key]->workToBeDone_ = false;
        } //end critical section
    }
    return std::make_shared<std::vector<std::shared_ptr<Job>>>(jobs);
}

bool JobTable::workToBeDone(std::string key)
{

    return validateKey(key) && dataMap_[key]->workToBeDone_;
}

std::condition_variable &JobTable::getCV(std::string key)
{
    assert(validateKey(key));
    return dataMap_[key]->cv_;
}

std::mutex &JobTable::getMutex(std::string key)
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

bool JobTable::validateKey(std::string key)
{
    return dataMap_.find(key) != dataMap_.end();
}