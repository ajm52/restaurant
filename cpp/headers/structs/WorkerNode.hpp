#ifndef WORKERNODE_HPP
#define WORKERNODE_HPP

#include <string>

/**
 * @struct <code>WorkerNode</code>
 * @description: Wrapper struct for a worker stat pair.
 * Used in MinHeap.
 * @author ajm
 * @created: 2/24/20
 * @modified: 3/2/20
 */
struct WorkerNode
{
    unsigned numJobs_;     ///< worker job count.
    std::string workerID_; ///< worker ID string.

    /**
     * @description: Constructor.
     * @param id worker id string.
     */
    WorkerNode(std::string id = "", unsigned jobs = 0) : numJobs_(jobs), workerID_(id) {}

    /**
     * @description: Copy constructor.
     * @param other object to be copied.
     */
    WorkerNode(const WorkerNode &other) : numJobs_(other.numJobs_), workerID_(other.workerID_) {}

    /**
     * @description: Copy assignment operator.
     * @param other object to be copied.
     * @returns <code>this</code> with other's parameters.
     */
    WorkerNode &operator=(const WorkerNode &other);

    /**
     * @description: Destructor.
     */
    ~WorkerNode() {}

    /**
     * @description: < operator overload.
     * @param rhs right-hand <code>WorkerNode</code> being compared.
     * @returns true if <code>this</code> is LT than rhs, false otherwise.
     * @note Uniqueness of Worker IDs ensures that no two WorkerNodes
     * can be equal, which is convenient.
     */
    bool operator<(const WorkerNode &rhs) const;

    /**
     * @description: <= operator overload.
     * @param rhs right-hand <code>WorkerNode</code> being compared.
     * @returns true if <code>this</code> is LTE than rhs, false otherwise.
     * @note Only implemented for compatibility with MinHeap correctness.
     */
    bool operator<=(const WorkerNode &rhs) const;

    /**
     * @description: == operator overload.
     * @param rhs right-hand <code>WorkerNode</code> being compared.
     * @returns true iff <code>this</code> is EQ to rhs, false otherwise.
     * @note Implemented so root index can be tracked and returned during minHeapify.
     */
    bool operator==(const WorkerNode &rhs) const;

    /**
     * @description: Decrement operator.
     * Lowers <code>this WorkerNode</code>'s job count by a given amount.
     * @param amt amount to decrement job count by.
     * @note job count >= 0.
     * @returns <code>this</code> with a modified job count.
     */
    WorkerNode &operator-=(int amt);

    /**
     * @description: Increment operator.
     * Raises <code>this WorkerNode</code>'s job count by a given amount.
     * @param amt amount to inrement job count by.
     * @returns <code>this</code> with a modified job count.
     */
    WorkerNode &operator+=(int amt);
};

/**
     * @description: Print method.
     * Required for Boost.Test; will also serve use for debugging.
     * @param out Output stream object.
     * @param n <code>WorkerNode</code> to be printed.
     * @returns the ostream object.
     */
std::ostream &operator<<(std::ostream &out, const WorkerNode &n);

#endif // WORKERNODE_HPP