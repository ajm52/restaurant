#include "GlobalClock.hpp"
#include <string>
#include <chrono>
#include <ostream>
#include <iomanip>
#include <ios>

GlobalClock::GlobalClock() : start_(std::chrono::high_resolution_clock::now()) {}

GlobalClock::GlobalClock(const GlobalClock &gc) : start_(gc.start_) {}

GlobalClock &GlobalClock::operator=(const GlobalClock &gc)
{
    if (this == &gc)
        return *this;
    start_ = gc.start_;
    return *this;
}

void GlobalClock::setStartTime()
{
    start_ = std::chrono::high_resolution_clock::now();
}

std::ostream &operator<<(std::ostream &out, const GlobalClock &gc)
{
    double del = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - gc.getStartTime()).count();
    out << "[" << std::fixed << std::setprecision(6) << del << "]";
    return out;
}