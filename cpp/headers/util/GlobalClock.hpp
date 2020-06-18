#ifndef GLOBALCLOCK_HPP
#define GLOBALCLOCK_HPP

#include <chrono>
#include <string>

/**
 * @class GlobalClock
 * @author ajm
 * @description: A class dedicated toward precisely timing the occurrence of various events.
 */
class GlobalClock
{
public:
    /**
     * @description: constructor.
     */
    GlobalClock();

    /**
     * @description: copy constructor.
     * @param gc clock we're copying from.
     */
    GlobalClock(const GlobalClock &);

    /**
     * @description: copy assignment operator.
     * @param gc clock we're copying from.
     * @returns a copied clock.
     */
    GlobalClock &operator=(const GlobalClock &);

    /**
     * @description: destructor.
     */
    ~GlobalClock() = default;

    /**
     * @description: Sets the clock start time to now.
     */
    void setStartTime();

    /**
     * @description: prints out elapsed simulation time in seconds.
     * @returns a string representing elapsed simulation time.
     */
    std::string elapsed();

private:
    std::chrono::high_resolution_clock::time_point start_; ///< marks the simulation start time.
};
#endif // GLOBALCLOCK_HPP