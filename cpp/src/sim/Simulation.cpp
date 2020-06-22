#include "Simulation.hpp"
#include "GlobalClock.hpp"
#include "Restaurant.hpp"
#include "Door.hpp"
#include "Waiter.hpp"
#include "Party.hpp"
#include "MenuEntry.hpp"
#include "MenuEntryKey.hpp"
#include "MenuEntryKeyComparator.hpp"
#include "Menu.hpp"
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
      partiesOutside_(),
      clock_() {}

void Simulation::init(std::string filepath)
{
    std::ifstream in;
    std::cout << "Simulation initializing..\nAttempting to open sim config from '" << filepath << "'." << std::endl;
    in.open(filepath);

    if (!in)
    {
        std::cout << "Sim config path error, trying 'meta/sim.md'.\n";
        in.open("meta/sim.md");
        if (!in)
        {
            std::cout << "Unable to open simulation config; exiting now.\n";
            exit(-1); //TODO Add a final option that asks user to supply a path or quit the program.
        }
    }

    std::string line;
    while (std::getline(in, line))
    {
        if (line.size() == 0 || line[0] == '#' || line[0] == ' ')
            continue;
        else
        {
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
    std::cout << ".\n.\n.\nSimulation initialization done; tCount=" << tableCount_ << ", wCount=" << waiterCount_ << ", pCount=" << partyCount_ << ".\n";
}

std::shared_ptr<Menu> Simulation::createMenu(std::string filepath)
{
    std::ifstream in;
    std::cout << "Simulation: Attempting to open menu config from '" << filepath << "'.\n";
    in.open(filepath);

    if (!in)
    {
        std::cout << "Menu config path error, trying 'cpp/meta/menu.md'.\n";
        in.open("cpp/meta/menu.md");
        if (!in)
        {
            std::cout << "Unable to open menu config; exiting now.\n";
            exit(-1); //TODO Add a final option that asks user to supply a path or quit the program.
        }
    }

    std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator> options;
    std::string line;

    while (std::getline(in, line))
    {
        if (line.size() == 0 || line[0] == '#' || line[0] == ' ')
            continue;

        if (line[0] == '-')
        {                                      // begins a menu section (i.e. food)
            char entryType = toupper(line[1]); //NOTE ensure line.size() > 1.
            unsigned num = 0;
            std::vector<std::string> tokens;

            std::getline(in, line);
            while (line[0] != '^') // '^' ends a section.
            {
                boost::algorithm::split(tokens, line, boost::algorithm::is_any_of(" "));
                // we expect to have 2 tokens per line.
                std::string dishName = tokens[0];
                unsigned prepTime = std::stoi(tokens[1]);

                options.insert(std::pair<MenuEntryKey, MenuEntry>(MenuEntryKey(entryType, num), MenuEntry(dishName, prepTime)));
                std::getline(in, line);
                num += 1;
            } // END WHILE
        }
    } // END WHILE

    in.close();
    return std::make_shared<Menu>(options);
}

void Simulation::run()
{
    clock_.setStartTime();

    std::cout << clock_ << " Simulation: Building Restaurant Menu...";
    std::shared_ptr<Menu> menu = createMenu("meta/menu.md");
    std::cout << " done.\n"
              << clock_ << " Simulation: Building Restaurant...";
    std::shared_ptr<Restaurant> r = std::make_shared<Restaurant>(clock_, menu, tableCount_, waiterCount_, partyCount_);
    std::cout << " done.\n"
              << clock_ << " Simulation: Building Parties...";
    buildSimParties(*r);
    std::cout << " done.\n";

    std::cout << clock_ << " Simulation: Initializing Restaurant...";
    r->init(); // sets up the restaurant (constructing tables, waiters, etc.)
    std::cout << " done.\n";

    int sleepCount = 0; // temporary fix to stop infinite while

    std::cout << clock_ << " Simulation: BEGINNING MAIN LOOP\n";
    while (true) // begin Simulation loop.
    {
        if (partiesOutside_.size() > 0) // if there is a party outside.. Bring one in.
        {                               // TODO add to the condition, so restaurant is not overpopulated (down the road)
            sleepCount = 0;
            unsigned pID = partiesOutside_.back();
            partiesOutside_.pop_back();
            auto pPtr = (simParties_)[pID];
            partiesInside_.push_back(pID);

            std::cout << clock_ << " Simulation: Spawning " << pPtr->getPID() << ".\n";
            pPtr->init(); // starts this Party's thread.
        }
        else
        {
            sleepCount++;
            std::cout << clock_ << " Simulation: No activity; Sleeping...\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }

        // if (sleepCount >= 2)
        // {
        //     std::cout << "Inactivity detected, quitting now.\n";
        //     break;
        // }

    } // end Simulation loop
}

void Simulation::buildSimParties(Restaurant &r)
{
    for (int i = 0; i < partyCount_; ++i)
    {
        std::string str = "P-" + std::to_string(i);
        auto pPtr = std::make_shared<Party>(clock_, r, 0, str);
        simParties_.push_back(pPtr);
        partiesOutside_.push_back(i);
    }
}