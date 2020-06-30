#ifndef BARTENDER_HPP
#define BARTENDER_HPP

#include "JobTable.hpp"
#include "Worker.hpp"
#include "GlobalClock.hpp"
#include "Menu.hpp"
#include <string>

struct Job;
struct OrderJob;

/**
 * @class Bartender
 * @author ajm
 * @description: A thread-based restaurant bartender. Completes drink orders for parties.
 */
class Bartender : public Worker
{
public:
    /**
     * @description: constructor.
     * @param gc simulation clock
     * @param jt job table
     * @param m restaurant menu
     * @param id bartender id string
     */
    Bartender(GlobalClock &gc, JobTable &jt, Menu &m, std::string id = "DEFAULT_BID")
        : Worker(gc, jt, m, id) {}

    /**
     * @description: handler method used to complete SeatingJobs.
     * @param sj job to be handled
     * NOTE Bartenders should never be assigned these types of 
     * Jobs; however, we provide an empty definition to satisfy
     * pure virtuality.
     * 
     * TODO throw an error here?
     */
    void handleJob(SeatingJob &) {}

    /**
     * @description: handler method used to complete OrderJobs.
     * @param oj job to be handled.
     */
    void handleJob(OrderJob &);

    Bartender(const Bartender &) = delete; ///< Bartender is neither copyable nor movable
    Bartender &operator=(const Bartender &) = delete;
    Bartender(Bartender &&) = delete;
    Bartender &operator=(Bartender &&) = delete;
};
#endif // BARTENDER_HPP

/**
 * TODO implement handleJob(OrderJob)
 */