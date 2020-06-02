#ifndef WORKER_H
#define WORKER_H

#include "Person.h"

/**
 * @class <code>Worker</code>
 * @description: A restaurant employee. Inherits from <code>Person</code>.
 * @author ajm
 * @created: 2/19/20
 * @modified: 6/2/20
 */
class Worker : public Person
{
public:
    /**
     * @description: constructor.
     * @param id worker id string.
     */
    Worker(std::string id = "DEFAULT_WID") : Person(id) {}

    /**
     * @description: destructor.
     */
    virtual ~Worker() = default;
};

/**
 * TODO: test this class, notably its I/O capabilities.
 */

#endif // WORKER_H