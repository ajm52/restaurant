#include <utility>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

#include "WorkerNode.h"
#include "MinHeap.h"

#include "WorkerBulletin.h"

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
    int index = heapIndices_[workerID];
    if (amt < 0)
        correctHeapIndices(minHeap_.decr(index, -amt));
    else
        correctHeapIndices(minHeap_.incr(index, amt));
}
