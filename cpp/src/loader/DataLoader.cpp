#include <memory>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <ctype.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "Menu.h"
#include "MenuEntry.h"
#include "MenuEntryKey.h"
#include "DataLoader.h"

struct MenuEntryKeyComparator;

/**
 * uses an ifstream object to read in metadata,
 * building and returning the Menu.
 *
 * TODO: add appropriate exception handling for file not found.
 * 
 * NOTE: parser should be robust against:
 * 
 **/
const Menu &DataLoader::createMenu()
{
    std::ifstream in;
    in.open("../../../../meta/menu.md");

    if (!in)
    {
        std::cout << "Unable to open file.\n"; //this should eventually be a logged exception
        exit(-1);
    }
    std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator> options;
    std::string line;
    while (std::getline(in, line))
    {
        if (line.size() == 0)
            continue; // not sure if possible; we will find out.

        // lines that begin with '-' signify the start of a menu section.
        // we know what section it is based on the first non '-' character. (i.e. f -> food)
        if (line[0] == '-')
        {
            char entryType = toupper(line[1]); // must be sure line.size() > 1
            unsigned num = 0;
            std::vector<std::string> tokens;

            std::getline(in, line);
            while (line[0] != '^') // '^' ends a menu section
            {
                boost::algorithm::split(tokens, line, boost::algorithm::is_any_of(" "));
                // we expect to have 2 tokens per line.
                std::shared_ptr<MenuEntryKey> key = makeMenuEntryKey(entryType, num);
            }
        }
    } // end while
    Menu *menu;
    return *menu;
}