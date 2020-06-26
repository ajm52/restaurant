#ifndef SIMMONITOR_HPP
#define SIMMONITOR_HPP

#include <string>

/**
 * @class SimMonitor
 * @author ajm
 * @description: A simulation "overseer" of sorts.
 * For now, its job will be only to distribute the 
 * next Order id.
 */
class SimMonitor
{
public:
    /**
     * @description: constructor.
     */
    SimMonitor() : orderCount_() {}

    /**
     * @description: destructor.
     */
    ~SimMonitor() = default;

    /**
     * @description: accessor for the next Order ID.
     * Should only be used by Parties submitting Orders.
     * @returns the next order ID.
     */
    std::string getNextOrderID();

private:
    unsigned orderCount_; ///< # of simulation orders made.
};
#endif // SIMMONITOR_HPP

/**
 * TODO move worker tally member data to this class (?)
 */