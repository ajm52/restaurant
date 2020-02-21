#include <math.h>
#include "MinHeap.h"

MinHeap::MinHeap() : heap_() {}

void MinHeap::minHeapify(int root)
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
            if (heap_[i] <= heap_[smallerChild])
                break;
            // swap heap_[i] and heap_[smallerChild]
            int temp = heap_[i];
            heap_[i] = heap_[smallerChild];
            heap_[smallerChild] = temp;
            i = smallerChild;
        }
    }
}
void MinHeap::insert(int value)
{
    heap_.push_back(value);
    minHeapify(getParent(heap_.size() - 1));
}