#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>

/**
 * @struct <code>MinHeap</code>
 * @description: a min heap.
 * @author ajm
 * @created: 2/21/20
 * @modified: 2/21/20
 */
struct MinHeap
{
    /**
     * @description: default constructor.
     */
    MinHeap();

    /**
     * @description: destructor.
     */
    ~MinHeap() {}

    /**
     * @description: finds parent index of a given index in the heap.
     * @param i index of the element whose parent index we seek.
     * @returns parent index of heap_[i].
     */
    inline int getParent(int i) { return floor((i - 1) / 2); }

    /**
     * @description: ensures the MinHeap invariant is held.
     * @param root index to start heapifying from.
     */
    void minHeapify(int);

    /**
     * @description: inserts data into the heap.
     * @param value data to be inserted.
     */
    void insert(int);

    std::vector<int> heap_; ///< the heap.
};

#endif // MINHEAP_H

/**
 * TODO: make this struct generic
 * so it can hold any type comparable data.
 */