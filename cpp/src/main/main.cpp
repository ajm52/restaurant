#include "Simulation.hpp"
#include <iostream>
#include <vector>
#include <string>

/**
 * @description: Main program of sim.
 * @author ajm
 * @created: 1/27/20
 * @modified: 6/3/20
 **/

int main(int argc, char **argv)
{
    std::string s("P-" + std::to_string(1));
    std::cout << s << std::endl;
    Simulation sim;
    sim.init("cpp/meta/sim.md");
    sim.run();
    return 0;
}