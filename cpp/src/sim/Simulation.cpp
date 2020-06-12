#include "Simulation.hpp"
#include "Restaurant.hpp"
#include "Door.hpp"
#include "Waiter.hpp"
#include "Party.hpp"
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <filesystem>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#define DEBUG_MODE

Simulation::Simulation()
    : simParties_(),
      partiesInside_(),
      partiesOutside_() {}

void Simulation::init(std::string filepath)
{
    std::ifstream in;
    std::cout << "attempting to open " << filepath << std::endl;
    in.open(filepath);

    if (!in)
    {
        std::cout << "Unable to open config from path: " + filepath + "; trying meta/sim.md\n";
        in.open("meta/sim.md");
        if (!in)
        {
            std::cout << "Unable to open config from path: meta/sim.md; Exiting now.\n";
            exit(-1); //NOTE will eventually add a crash handler here.
        }
    }
    std::string line;
    while (std::getline(in, line))
    {
        if (line.size() == 0 || line[0] == '#' || line[0] == ' ')
            continue;
        else
        { // check against expected syntax.
            std::vector<std::string> tokens;
            boost::algorithm::split(tokens, line, boost::algorithm::is_any_of("="));

            if (tokens.size() > 1)
            {
                if (tokens[0] == "TABLE_COUNT")
                {
                    tableCount_ = std::stoi(tokens[1]);
                }
                else if (tokens[0] == "WAITER_COUNT")
                {
                    waiterCount_ = std::stoi(tokens[1]);
                }
                else if (tokens[0] == "PARTY_COUNT")
                {
                    partyCount_ = std::stoi(tokens[1]);
                }
            }
        }
    }

    in.close();
}

void Simulation::run()
{
    std::cout << "Sim is running.\n";
    std::cout << "tCount=" << tableCount_ << " wCount=" << waiterCount_ << " pCount=" << partyCount_ << std::endl;

    std::shared_ptr<Restaurant> r = std::make_shared<Restaurant>(tableCount_, waiterCount_, partyCount_);
    buildSimParties(*r);
    r->init();
    int sleepCount = 0;
    while (true)
    {
        if (partiesOutside_.size() > 0)
        {
            sleepCount = 0;
            unsigned pID = partiesOutside_.back();
            partiesOutside_.pop_back();
            std::cout << "here\n";
            auto pPtr = (simParties_)[pID - 1];
            std::cout << "there\n";
            partiesInside_.push_back(pID);
            std::cout << "booting up " << pPtr->getPID() << "\n";
            //p->init();
        }
        else
        {
            sleepCount++;
            std::cout << "restaurant cap is met. Sleeping...\n";
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }

        if (sleepCount >= 2)
        {
            std::cout << "inactivity detected, quitting now.\n";
            break;
        }
    }
}

void Simulation::buildSimParties(Restaurant &r)
{
#ifdef DEBUG_MODE
    std::cout << "building sim parties\n";
#endif // DEBUG_MODE
    for (int i = 1; i <= partyCount_; ++i)
    {
        std::string str = "P-" + std::to_string(i);
        auto pPtr = std::make_shared<Party>(r, 0, str);
        simParties_.push_back(pPtr);
        partiesOutside_.push_back(i);
#ifdef DEBUG_MODE
        std::cout << "fart\n";
        std::cout << "built " << simParties_.at(simParties_.size() - 1)->getPID() << std::endl;
#endif // DEBUG_MODE
    }
}