#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include "WorkerNode.hpp"
#include <cmath>
#include <vector>
#include <map>

/**
 * @struct MinHeap
 * @description: A generic min heap.
 * @author ajm
 */
template <typename T>
struct MinHeap
{
    /**
     * @description: constructor.
     */
    MinHeap() : heap_() {}

    /**
     * @description: destructor.
     */
    ~MinHeap() = default;

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
    std::map<T, int> minHeapify(int root)
    {
        int size = heap_.size();
        bool swapped = false;
        std::map<T, int> tracker;

        for (int i = root; i >= 0; --i)
        {
            while (true)
            {
                int leftChild = 2 * i + 1;
                if (leftChild < 0 || leftChild >= size)
                    break;
                int rightChild = 2 * i + 2;
                int smallerChild = leftChild;
                if (rightChild < size && heap_[rightChild] < heap_[leftChild])
                    smallerChild = rightChild;

                if (heap_[i] <= heap_[smallerChild])
                    break;

                // index tracking
                tracker[heap_[i]] = smallerChild;
                tracker[heap_[smallerChild]] = i;

                // swap heap_[i] and heap_[smallerChild]
                swapped = true;
                T temp = heap_[i];
                heap_[i] = heap_[smallerChild];
                heap_[smallerChild] = temp;
                i = smallerChild;
            }
        }
        if (!swapped) // avoids bad access
            tracker[heap_[root]] = root;

        return tracker;
    }

    /**
     * @description: inserts data into the heap.
     * @param value data to be inserted.
     * @returns a map, where each entry represents an element that has
     * changed positions and it's new index.
     */
    std::map<T, int> insert(const T &value)
    {
        heap_.push_back(value);
        return minHeapify((int)heap_.size() - 1);
    }

    /**
     * @description: Decrements the node at a given index.
     * @param index index of the node to decrement.
     * @param amt amount to decrement by.
     * @returns a map, where each entry represents an element that has
     * changed positions and it's new index.
     */
    inline std::map<T, int> decr(int index, int amt = 1)
    {
        heap_[index] -= amt;
        return minHeapify(index);
    }

    /**
     * @description: Increments the node at the given index.
     * @param index index of the node to increment.
     * @param amt amount to increment by.
     * @returns a map, where each entry represents an element that has
     * changed positions and it's new index.
     */
    inline std::map<T, int> incr(int index, int amt = 1)
    {
        heap_[index] += amt;
        return minHeapify(index);
    }

    /**
     * @description: Returns the heap's top node.
     */
    inline T top() const
    {
        return heap_[0];
    }

    /**
     * @description: prints heap contents in a linear fashion; semi-useful for debugging.
     * @note this method should see some improvement, such that contents are printed
     * in a more readable, heap-like fashion.
     */
    void printHeap();

    std::vector<T> heap_; ///< the heap.
};

#endif // MINHEAP_HPP

/**
 * TODO: Implement a HeapEmpty exception for when top is called and size == 0.
 * 
 * TODO: modify MinHeap_T to test top().
 * 
 * TODO: make printHeap() output more readable.
 * 
 * TODO: investigate resource cleanup of heap nodes;
 * would calling 'delete' from WorkerBulletin
 * automatically call the dtor, or how would this work?
 */