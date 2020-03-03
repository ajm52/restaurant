#include "WorkerNode.h"
#include <ostream>
#include <string>

WorkerNode &WorkerNode::operator=(const WorkerNode &other)
{
    if (this == &other)
        return *this;
    this->numJobs_ = other.numJobs_;
    this->workerID_ = other.workerID_;
    return *this;
}

bool WorkerNode::operator<(const WorkerNode &rhs) const
{
    if (numJobs_ < rhs.numJobs_)
        return true;
    else if (rhs.numJobs_ < numJobs_)
        return false;
    else
        return workerID_.compare(rhs.workerID_) < 0 ? true : false;
}

bool WorkerNode::operator<=(const WorkerNode &rhs) const
{
    if (numJobs_ < rhs.numJobs_)
        return true;
    else if (rhs.numJobs_ < numJobs_)
        return false;
    else
    {
        return workerID_.compare(rhs.workerID_) <= 0 ? true : false;
    }
}

bool WorkerNode::operator==(const WorkerNode &rhs) const
{
    if (numJobs_ == rhs.numJobs_ && workerID_ == rhs.workerID_)
        return true;
    else
    {
        return false;
    }
}

WorkerNode &WorkerNode::operator-=(int amt)
{
    numJobs_ = numJobs_ < amt ? 0 : numJobs_ - amt;
    return *this;
}

WorkerNode &WorkerNode::operator+=(int amt)
{
    numJobs_ += amt;
    return *this;
}

std::ostream &operator<<(std::ostream &out, const WorkerNode &n)
{
    out << n.workerID_ << "-" << n.numJobs_;
    return out;
}