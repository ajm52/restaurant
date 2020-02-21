#include "Queue.h"

Queue::Queue()
{
    head_ = nullptr;
    tail_ = new Node;
    size_ = 0;
}

Queue::~Queue()
{
    Node *current = tail_;
    while (current != nullptr)
    {
        Node *next = current->next_;
        delete current;
        current = next;
    }
}

void Queue::enqueue(int value)
{
    if (tail_->next_ == nullptr) // empty list
    {
        head_ = new Node(value);
        head_->prev_ = tail_;
        tail_->next_ = head_;
    }
    else
    { // list size >= 1
        Node *tailNext = tail_->next_;
        Node *toInsert = new Node(value);
        toInsert->next_ = tailNext;
        toInsert->prev_ = tail_;
        tailNext->prev_ = toInsert;
        tail_->next_ = toInsert;
    }
    size_ += 1;
}

int Queue::dequeue()
{
    size_ -= 1;

    if (head_ == nullptr) // empty list
        return -1;
    else
    { // head's prev becomes new head
        int toReturn = head_->value_;
        Node *toDelete = head_;
        head_ = head_->prev_;
        head_->next_ = nullptr;
        delete toDelete;
        return toReturn;
    }
}