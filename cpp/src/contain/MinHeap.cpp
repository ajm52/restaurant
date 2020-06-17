#include "MinHeap.hpp"
#include "WorkerNode.hpp"
#include <cmath>
#include <iostream>

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