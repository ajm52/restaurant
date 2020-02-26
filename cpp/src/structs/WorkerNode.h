#ifndef WORKERNODE_H
#define WORKERNODE_H

#include <ostream>
#include <string>

/**
 * @struct <code>WorkerNode</code>
 * @description: Wrapper struct for a worker stat pair.
 * Used in MinHeap.
 * @author ajm
 * @created: 2/24/20
 * @modified: 2/26/20
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
    WorkerNode &operator=(const WorkerNode &other)
    {
        if (this == &other)
            return *this;
        this->numJobs_ = other.numJobs_;
        this->workerID_ = other.workerID_;
        return *this;
    }

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
    bool operator<(const WorkerNode &rhs) const
    {
        if (numJobs_ < rhs.numJobs_)
            return true;
        else if (rhs.numJobs_ < numJobs_)
            return false;
        else
            return workerID_.compare(rhs.workerID_) < 0 ? true : false;
    }

    /**
     * @description: <= operator overload.
     * @param rhs right-hand <code>WorkerNode</code> being compared.
     * @returns true if <code>this</code> is LTE than rhs, false otherwise.
     * @note Only implemented for compatibility with MinHeap correctness.
     */
    bool operator<=(const WorkerNode &rhs) const
    {
        if (numJobs_ < rhs.numJobs_)
            return true;
        else if (rhs.numJobs_ < numJobs_)
            return false;
        else
        {
            return workerID_.compare(rhs.workerID_) <= 0 ? true : false;
        }
    }

    /**
     * @description: == operator overload.
     * @param rhs right-hand <code>WorkerNode</code> being compared.
     * @returns true iff <code>this</code> is EQ to rhs, false otherwise.
     * @note Implemented so root index can be tracked and returned during minHeapify.
     */
    bool operator==(const WorkerNode &rhs) const
    {
        if (numJobs_ == rhs.numJobs_ && workerID_ == rhs.workerID_)
            return true;
        else
        {
            return false;
        }
    }

    /**
     * @description: Decrement operator.
     * Lowers <code>this WorkerNode</code>'s job count by 1.
     * @returns <code>this</code> with a modified job count.
     */
    void operator--()
    {
        if (numJobs_ > 0)
            numJobs_ -= 1;
    }

    /**
     * @description: Increment operator.
     * Raises <code>this WorkerNode</code>'s job count by 1.
     * @returns <code>this</code> with a modified job count.
     */
    void operator++()
    {
        numJobs_ += 1;
    }

    /**
     * @description: Print method.
     * Required for Boost.Test; will also serve use for debugging.
     * @param out Output stream object.
     * @param n <code>WorkerNode</code> to be printed.
     * @returns the ostream object.
     */
    friend std::ostream &operator<<(std::ostream &out, const WorkerNode &n)
    {
        out << n.workerID_ << "-" << n.numJobs_;
        return out;
    }
};

#endif // WORKERNODE_H