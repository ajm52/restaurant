#ifndef QUEUE_HPP
#define QUEUE_HPP

/**
 * @struct Node
 * @description: Element of the doubly linked list.
 * @author ajm
 */
struct Node
{
    int value_;  ///< data.
    Node *next_; ///< next node in the list.
    Node *prev_; ///< previous node in the list.

    /**
     * @description: constructor.
     * @param val data to be held.
     */
    Node(int val = -1) : value_(val), next_(nullptr), prev_(nullptr) {}
};

/**
 * TODO: template the value member of Node (generic programming).
 */

/**
 * @struct Queue
 * @description: Doubly Linked List style.
 * @author ajm
 */
struct Queue
{
    /**
     * @description: constructor.
     */
    Queue();

    /**
     * @description: destructor. 
     */
    ~Queue();

    /**
     * @description: adds a Node with supplied data to end of the list.
     * @param value data to be held.
     */
    void enqueue(int);

    /**
     * @description: removes head of the list and returns it's data. Head's prev
     * becomes the new head.
     * @returns head's data.
     */
    int dequeue();

    Node *head_; ///< head of the list.
    Node *tail_; ///< tail of the list.
    int size_;   ///< list size.
};

#endif // QUEUE_HPP