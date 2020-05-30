#include "JobTable.h"
#include "Job.h"
#include <vector>
#include <mutex>
#include <memory>

void JobTable::queueJob(unsigned index, Job job)
{
    if (index >= mList_.size()) //TODO throw an exception here.
        return;
    { //begin critical section
        std::lock_guard<std::mutex> lg(mList_[index]);
        jobQueues_[index].push(job);
    } //end critical section
    cvList_[index].notify_one();
}

Job *JobTable::acquireJob(unsigned index)
{
    if (index >= mList_.size() || jobQueues_[index].size() == 0) //TODO throw an exception here.
        return nullptr;
    Job *job;
    { //begin critical section
        std::lock_guard<std::mutex> lg(mList_[index]);
        job = &(jobQueues_[index].front());
        jobQueues_[index].pop();
    } //end critical section
    return job;
}

std::shared_ptr<std::vector<Job>> JobTable::acquireAllJobs(unsigned index)
{
    std::vector<Job> jobs;
    if (index < mList_.size() && jobQueues_[index].size() > 0)
    {
        { //begin critical section
            std::lock_guard<std::mutex> lg(mList_[index]);
            while (!jobQueues_[index].empty())
            {
                Job j = jobQueues_[index].front();
                jobQueues_[index].pop();
                jobs.push_back(j);
            }
        } //end critical section
    }
    return std::make_shared<std::vector<Job>>(jobs);
}