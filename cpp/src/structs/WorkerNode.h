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
 * @modified: 2/24/20
 */
struct WorkerNode
{
    unsigned numJobs_;     ///< worker job count.
    std::string workerID_; ///< worker ID string.

    /**
     * @description: Constructor.
     * @param id worker id string.
     */
    WorkerNode(std::string id) : numJobs_(0), workerID_(id) {}

    /**
     * @description: Destructor.
     */
    ~WorkerNode() {}

    /**
     * @description: Comparison method.
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
            return workerID_.compare(rhs.workerID_);
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