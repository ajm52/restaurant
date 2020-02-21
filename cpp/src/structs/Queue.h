#ifndef QUEUE_H
#define QUEUE_H

/**
 * @struct <code>Node</code>
 * @description: Element of the doubly linked list.
 * @author ajm
 * @created: 2/21/20
 * @modified: 2/21/20
 */
struct Node
{
    int value_;  ///< data.
    Node *next_; ///< next node in the list.
    Node *prev_; ///< previous node in the list.

    /**
     * @description: default constructor.
     * @param val data to be held.
     */
    Node(int val = -1) : value_(val), next_(nullptr), prev_(nullptr) {}
};

/**
 * TODO: template the value member of Node (generic programming).
 */

/**
 * @struct <code>Queue</code>
 * @description: Doubly Linked List style.
 * @author ajm
 * @created: 2/21/20
 * @modified: 2/21/20
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
     * @description: adds <code>Node</code> with supplied data to end of the list.
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

#endif // QUEUE_H