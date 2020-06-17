#ifndef WORKER_HPP
#define WORKER_HPP

#include "Person.hpp"

struct SeatingJob;
struct OrderJob;

/**
 * @class Worker
 * @description: A restaurant employee. Inherits from Person.
 * @author ajm
 * @note In order to take full advantage of runtime polymorphism 
 * with the Visitor pattern, all handleJob(Job) methods must be 
 * pure virtual. That said, Worker subclasses must provide
 * definitions for all handleJob methods to make the compiler happy.
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

    /**
     * @description: pure virtual seating job handler. 
     * @param sj a seating job.
     */
    virtual void handleJob(SeatingJob &) = 0;

    /**
     * @description: pure virtual order job handler.
     * @param oj an order job.
     */
    virtual void handleJob(OrderJob &) = 0;
};

/**
 * TODO: test this class.
 */

#endif // WORKER_HPP