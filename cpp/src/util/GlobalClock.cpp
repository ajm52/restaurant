#include "GlobalClock.hpp"
#include <string>
#include <chrono>

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

std::string GlobalClock::elapsed()
{
    return "[" + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_).count()) + "]";
}