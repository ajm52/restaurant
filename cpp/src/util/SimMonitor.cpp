#include "SimMonitor.hpp"
#include <string>

std::string SimMonitor::getNextOrderID()
{
    return "O" + std::to_string(orderCount_++);
}
