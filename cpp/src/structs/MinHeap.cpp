#include <math.h>
#include <ostream>
#include "MinHeap.h"

template <typename T>
MinHeap<T>::MinHeap() : heap_() {}

template <typename T>
int MinHeap<T>::minHeapify(int root)
{
    int size = heap_.size();
    int retIndex = root;

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

            // tracking root index that must be returned.
            // reversed, as the index saving is pre-swap.
            if (heap_[i] == heap_[root])
                retIndex = smallerChild;
            else if (heap_[smallerChild] == heap_[root])
                retIndex = i;

            // swap heap_[i] and heap_[smallerChild]
            T temp = heap_[i];
            heap_[i] = heap_[smallerChild];
            heap_[smallerChild] = temp;
            i = smallerChild;
        }
    }

    return retIndex;
}

template <typename T>
int MinHeap<T>::insert(const T &value)
{
    heap_.push_back(value);
    return minHeapify(heap_.size() - 1);
}

template <typename T>
int MinHeap<T>::decr(int index)
{
    --heap_[index];
    return minHeapify(index);
}

template <typename T>
int MinHeap<T>::incr(int index)
{
    ++heap_[index];
    return minHeapify(index);
}

template <typename T>
void MinHeap<T>::printHeap()
{
    std::cout << "heap: ";
    for (int i = 0; i < heap_.size(); ++i)
    {
        std::cout << heap_[i] << ", ";
    }
    std::cout << "\n";
}