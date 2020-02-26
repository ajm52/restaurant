#include <math.h>
#include <ostream>
#include "MinHeap.h"

template <typename T>
MinHeap<T>::MinHeap() : heap_() {}

template <typename T>
std::map<T, int> MinHeap<T>::minHeapify(int root)
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

template <typename T>
std::map<T, int> MinHeap<T>::insert(const T &value)
{
    heap_.push_back(value);
    return minHeapify((int)heap_.size() - 1);
}

template <typename T>
std::map<T, int> MinHeap<T>::decr(int index)
{
    --heap_[index];
    return minHeapify(index);
}

template <typename T>
std::map<T, int> MinHeap<T>::incr(int index)
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