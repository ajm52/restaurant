#ifndef GLOBALCLOCK_HPP
#define GLOBALCLOCK_HPP

#include <chrono>
#include <string>
#include <ostream>

/**
 * @class GlobalClock
 * @author ajm
 * @description: A class dedicated to the precise timing of program events.
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
     * @description: start time accessor.
     * @returns time point representing the clock's start time.
     */
    inline const std::chrono::high_resolution_clock::time_point &getStartTime() const { return start_; }

    /**
     * @description: print function that makes outputting clock time easy.
     * Displays time in seconds to 6 decimal places.
     * @param out an output stream
     * @param gc the clock
     * @returns output stream
     */
    friend std::ostream &operator<<(std::ostream &, const GlobalClock &);

private:
    std::chrono::high_resolution_clock::time_point start_; ///< marks the simulation start time.
};

#endif // GLOBALCLOCK_HPP