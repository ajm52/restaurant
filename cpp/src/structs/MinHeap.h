#ifndef MINHEAP_H
#define MINHEAP_H

#include <map>
#include <vector>

#include "WorkerNode.h"

/**
 * @struct <code>MinHeap</code>
 * @description: A generic min heap.
 * @author ajm
 * @created: 2/21/20
 * @modified: 2/26/20
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
     * @description: alternative minHeapify algorithm, useful
     * when elements indices are being tracked by client code.
     * @param root index to start heapifying from.
     * @returns a map, where each entry represents an element that has
     * changed positions in the heap (std::pair<old index, new index>).
     */
    std::map<T, int> minHeapify(int);

    /**
     * @description: inserts data into the heap.
     * @param value data to be inserted.
     * @returns a map, where each entry represents an element that has
     * changed positions and it's new index.
     */
    std::map<T, int> insert(const T &);

    /**
     * @description: Decrements the node at a given index.
     * @param index index of the node to decrement.
     * @param amt amount to decrement by.
     * @returns a map, where each entry represents an element that has
     * changed positions and it's new index.
     */
    std::map<T, int> decr(int, int);

    /**
     * @description: Increments the node at the given index.
     * @param index index of the node to increment.
     * @param amt amount to increment by.
     * @returns a map, where each entry represents an element that has
     * changed positions and it's new index.
     */
    std::map<T, int> incr(int, int);

    /**
     * @description: prints heap contents in a linear fashion; semi-useful for debugging.
     * @note this method should see some improvement, such that contents are printed
     * in a more readable, heap-like fashion.
     */
    void printHeap();

    std::vector<T> heap_; ///< the heap.
};

#endif // MINHEAP_H

/**
 * TODO: make printHeap() output more readable.
 * 
 * TODO: investigate resource cleanup of heap nodes;
 * would calling 'delete' from WorkerBulletin
 * automatically call the dtor, or how would this work?
 */