#ifndef WORKER_HPP
#define WORKER_HPP

#include "Person.hpp"

struct SeatingJob;
struct OrderJob;

/**
 * @class <code>Worker</code>
 * @description: A restaurant employee. Inherits from <code>Person</code>.
 * @author ajm
 * @created: 2/19/20
 * @modified: 6/3/20
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

    virtual void handleJob(SeatingJob *){};
    virtual void handleJob(OrderJob *){};
};

/**
 * TODO: test this class.
 */

#endif // WORKER_HPP