#ifndef WAITERBULLETIN_H
#define WAITERBULLETIN_H

#include <boost/tuple/tuple.hpp>

#include <utility>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

#include "Waiter.h"

typedef std::pair<std::string, int> HeapPair; ///< for brevity.

/**
 * @class <code>WaiterBulletin</code>
 * @description: Contains waiter-related information.
 * Will be of use mostly for door callback function(s).
 * @note we implement the MinHeap so that determining the 
 * Least Busy Waiter (LBW) can be done in O(1).
 * @author ajm
 * @created: 2/20/20
 * @modified: 2/20/20
 */
class WaiterTable
{
public:
private:
    int heapSize_;                           ///< size of heap.
    std::map<std::string, int> waiterFDs_;   ///< maps waiter ID to FD.
    std::map<std::string, int> heapIndices_; ///< maps waiter ID to heap index.
    std::vector<HeapPair> waiterMinHeap_;    ///< MinHeap of <waiter ID, job count> tuples.

    int getHeapParentIndex(int index)
    {
    }

    void minHeapify(int root)
    {
        if (root < 0 || root > heapSize_)
            return;
        for (int i = root; i >= 0; --i)
        {
            while (true)
            {
                int leftChild = 2 * i + 1;
                if (leftChild >= heapSize_)
                    break;

                int rightChild = 2 * i + 2;
                int smallerChild = leftChild;
                if (rightChild < heapSize_ &&
                    cmpHeapPairs(waiterMinHeap_[leftChild], waiterMinHeap_[rightChild]) > 0)
                    smallerChild = rightChild;

                if (cmpHeapPairs(waiterMinHeap_[smallerChild], waiterMinHeap_[i]) > 0)
                    break;
                // swap in heapIndices.
                std::swap(heapIndices_[waiterMinHeap_[smallerChild].first],
                          heapIndices_[waiterMinHeap_[i].first]);
                // swap in minHeap.
                std::swap(waiterMinHeap_[smallerChild], waiterMinHeap_[i]);

                i = smallerChild;
            }
        }
    }

    void registerWaiter(Waiter w)
    {
        /// when Waiter has it's own FD, must put that in the fdMap.
        std::pair<std::string, int> indexPair = std::make_pair(w.getId(), heapSize_);
        heapIndices_.insert(indexPair);
        HeapPair heapPair = std::make_pair(w.getId(), 0);
        waiterMinHeap_.push_back(heapPair);
        heapSize_ += 1;
    }
};

/**
 * @description: <code>HeapPair</code> comparator.
 * @param lhs left-hand <code>HeapPair</code> in comparison.
 * @param rhs right-hand <code>HeapPair</code> in comparison.
 * @returns <code>false</code> if lhs's job count is lower, true
 * otherwise. If job counts are equal, the <code>HeapPair</code> with the 
 * lexicographically smaller waiter ID breaks the tie.
 * For example, <code>compHeapPairs(<1,W0>, <1,W1>) == false.</code>
 */
int cmpHeapPairs(HeapPair lhs, HeapPair rhs)
{
    if (lhs.second < rhs.second)
        return -1;
    else if (lhs.second > rhs.second)
        return 1;
    else
        return lhs.first.compare(rhs.first);
}

#endif // WAITERBULLETIN_H