#include <math.h>
#include "MinHeap.h"

template <typename T>
MinHeap<T>::MinHeap() : heap_() {}

template <typename T>
void MinHeap<T>::minHeapify(int root)
{
    int size = heap_.size();
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
            /**
             * The uniqueness of intended data to 
             * be used (i.e. WorkerNodes), makes '<='
             * unnecessary and would just require
             * another operator to be overloaded,
             * so we stick with '<'.
             */
            if (heap_[i] < heap_[smallerChild])
                break;
            // swap heap_[i] and heap_[smallerChild]
            T &temp = heap_[i];
            heap_[i] = heap_[smallerChild];
            heap_[smallerChild] = temp;
            i = smallerChild;
        }
    }
}

template <typename T>
void MinHeap<T>::insert(const T &value)
{
    heap_.push_back(value);
    minHeapify(getParent(heap_.size() - 1));
}