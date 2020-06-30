#ifndef WORKERJOBDATA_HPP
#define WORKERJOBDATA_HPP

#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

struct Job;

/**
 * @struct WorkerJobData
 * @author ajm
 * @description: A struct to be used as a map value in JobTable.
 * Contains data related to assigning/acquiring work: a job queue, mutex/CV for assigning/acquiring said jobs, and a flag.
 */
struct WorkerJobData
{
    /**
     * @description: constructor.
     */
    WorkerJobData() : workToBeDone_(false), m_(), cv_(), jobs_() {}

    /**
     * @description: destructor.
     */
    ~WorkerJobData() = default;

    WorkerJobData(const WorkerJobData &) = delete; ///< WorkerJobData is neither copyable nor movable.
    WorkerJobData &operator=(const WorkerJobData &) = delete;
    WorkerJobData(WorkerJobData &&) = delete;
    WorkerJobData &operator=(WorkerJobData &&) = delete;

    mutable bool workToBeDone_;             ///< worker job flag.
    mutable std::mutex m_;                  ///< worker mutex.
    mutable std::condition_variable cv_;    ///< worker condition variable.
    std::queue<std::shared_ptr<Job>> jobs_; ///< worker job queue.
};
#endif // WORKERJOBDATA_HPP