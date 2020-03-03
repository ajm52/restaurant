#include "WorkerBulletin.h"
#include "WorkerNode.h"
#include "MinHeap.h"
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <mutex>

WorkerBulletin::~WorkerBulletin()
{
}

void WorkerBulletin::correctHeapIndices(std::map<WorkerNode, int> changes)
{
    for (auto pair : changes)
        heapIndices_[pair.first.workerID_] = pair.second;
}

void WorkerBulletin::registerWorker(Worker w)
{
    workerFDs_[w.getId()] = w.getFD();
    std::map<WorkerNode, int> changes = minHeap_.insert(*(new WorkerNode(w.getId())));
    correctHeapIndices(changes);
}

void WorkerBulletin::modifyJobCount(std::string workerID, int amt)
{
    std::lock_guard<std::mutex> lg(m_); // lock before modifying
    int index = heapIndices_[workerID];
    if (amt < 0)
        correctHeapIndices(minHeap_.decr(index, -amt));
    else
        correctHeapIndices(minHeap_.incr(index, amt));
}

int WorkerBulletin::LBW() const
{
    std::string lbw;
    {
        std::lock_guard<std::mutex> lg(m_); // lock before reading
        lbw = minHeap_.top().workerID_;
    }
    return workerFDs_.at(lbw);
}
