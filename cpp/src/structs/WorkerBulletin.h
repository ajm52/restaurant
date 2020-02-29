#ifndef WORKERBULLETIN_H
#define WORKERBULLETIN_H

#include "Worker.h"

class WorkerNode;

template <typename T>
class MinHeap;

/**
 * @struct <code>WorkerBulletin</code>
 * @description: Contains worker-related information.
 * Will be of use mostly for door callback function(s).
 * @note we implement the MinHeap so that determining the 
 * Least Busy Worker (LBW) can be done in O(1).
 * @author ajm
 * @created: 2/20/20
 * @modified: 2/28/20
 */
struct WorkerBulletin
{
    int size_;                               ///< size of heap.
    std::map<std::string, int> workerFDs_;   ///< maps worker ID to FD.
    std::map<std::string, int> heapIndices_; ///< maps worker ID to heap index.
    MinHeap<WorkerNode> minHeap_;            ///< worker min heap.

    /**
     * @description: Constructor.
     */
    WorkerBulletin() : size_(0), workerFDs_(), heapIndices_(), minHeap_() {}

    /**
     * @description: Destructor.
     */
    ~WorkerBulletin();

    /**
     * @description: Ensures that worker heap indices here reflect
     * the actual worker indices in <code>MinHeap</code>.
     * @param changes a mapping of <code><WorkerNode,newIndex></code>
     * changes to be recorded.
     */
    void correctHeapIndices(std::map<WorkerNode, int>);

    /**
     * @description: Adds a worker to the bulletin, which includes
     * recording its file descriptor and adding it to the heap.
     * @param w worker to be added.
     */
    void registerWorker(Worker);

    /**
     * @description: Adjusts job count of a worker by a given amount.
     * @param workerID worker id whose count we're decrementing.
     * @param amt amount to adjust worker's job count by.
     */
    void modifyJobCount(std::string, int);
};

/**
 * TODO: add a mutex for concurrent LBW access.
 */

#endif // WORKERBULLETIN_H