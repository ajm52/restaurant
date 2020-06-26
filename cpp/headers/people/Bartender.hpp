#ifndef BARTENDER_HPP
#define BARTENDER_HPP

#include "JobTable.hpp"
#include "Worker.hpp"
#include "GlobalClock.hpp"
#include "Menu.hpp"
#include <string>
#include <memory>

struct Job;
struct OrderJob;

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
    Bartender(GlobalClock &gc, JobTable &jt, std::shared_ptr<Menu> m, std::string id = "DEFAULT_BID")
        : Worker(gc, jt, m, id) {}

    /**
     * @description: move constructor.
     * @param b bartender being moved
     */
    Bartender(Bartender &&);

    /**
     * @description: move assignment operator.
     * @param b bartender being moved
     * @returns this bartender.
     */
    Bartender &operator=(Bartender &&);

    /**
     * @description: accessor for the numeric half of this 
     * bartender's id.
     * @returns the numeric half of this bartender's id.
     */
    const int getIDNumber() const;

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

private:
    Bartender(const Bartender &) = delete;
    Bartender &operator=(const Bartender &) = delete;
};
#endif // BARTENDER_HPP

/**
 * TODO once we have switched to string-based keys in JobTable, remove getIDNumber().
 */