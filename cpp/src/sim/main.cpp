#include "Simulation.hpp"
#include <iostream>
#include <vector>
#include <string>

/**
 * @description: Main program of sim.
 * @author ajm
 **/

int main(int argc, char **argv)
{
    Simulation sim;
    sim.init("cpp/meta/sim.md");
    sim.run();
    return 0;
}