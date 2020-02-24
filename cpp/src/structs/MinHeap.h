#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>

/**
 * @struct <code>MinHeap</code>
 * @description: A generic min heap.
 * @author ajm
 * @created: 2/21/20
 * @modified: 2/24/20
 */
template <typename T>
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
     * @returns new root index after minHeapify.
     */
    int minHeapify(int);

    /**
     * @description: inserts data into the heap.
     * @param value data to be inserted.
     * @returns index of T in the heap.
     */
    int insert(const T &);

    /**
     * @description: Decrements the node at a given index.
     * @param index index of the node to decrement.
     * @returns index of the decremented node after minHeapify.
     */
    int decr(int);

    /**
     * @description: Increments the node at the given index.
     * @param index index of the node to increment.
     * @returns index of the incremented node after minHeapify.
     */
    int incr(int);

    void printHeap();

    std::vector<T> heap_; ///< the heap.
};

#endif // MINHEAP_H

/**
 * 
 * TODO: investigate resource cleanup of heap nodes;
 * would calling 'delete' from WorkerBulletin
 * automatically call the dtor, or how would this work?
 */