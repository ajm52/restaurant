#ifndef WORKER_H
#define WORKER_H

#include "Person.h"

/**
 * @class <code>Worker</code>
 * @description: A restaurant employee. Inherits from <code>Person</code>.
 * @author ajm
 * @created: 2/19/20
 * @modified: 3/4/20
 */
class Worker : public Person
{
public:
    /**
     * @description: constructor.
     * @param fd worker fd.
     * @param id worker id string.
     */
    Worker(int fd = 0, std::string id = "DEFAULT_PID") : fd_(fd), Person(id) {}

    /**
     * @description: destructor.
     */
    virtual ~Worker() = default;

    /**
     * @description: fd accessor.
     * @returns worker's fd.
     */
    inline int getFD() const { return fd_; }

private:
    int fd_; ///< file descriptor.
};

/**
 * TODO: test this class, notably its I/O capabilities.
 */

#endif // WORKER_H