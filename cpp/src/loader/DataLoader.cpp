#include "DataLoader.h"
#include "MenuEntryKey.h"
#include "MenuEntry.h"
#include "Menu.cpp"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <ctype.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

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
const std::shared_ptr<Menu> DataLoader::createMenu()
{
    std::ifstream in;
    in.open("../../../meta/menu.md");

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
                std::string dishName = tokens[0];
                unsigned prepTime = std::stoi(tokens[1]);
                // insert menu entry
                options.insert(std::pair<MenuEntryKey, MenuEntry>(MenuEntryKey(entryType, num), MenuEntry(dishName, prepTime)));

                std::getline(in, line);
                num += 1;
            }
        }
    } // end while
    return std::shared_ptr<Menu>(new Menu(options));
}

/**
 * TODO: Alter this method so that it takes 2 params,
 * count and starting port. SimLoader will read the file
 * and pass that info in, no need for multiple methods to
 * read the file.
 */
const std::shared_ptr<std::vector<int>> createFDs(std::string filepath)
{
    std::ifstream in;
    in.open(filepath);
    if (!in)
    {
        std::cout << "bad filepath, exiting.\n";
        exit(-1);
    }
    std::vector<int> descriptors;
    std::vector<std::string> tokens;
    std::string line;
    while (std::getline(in, line))
    {
        if (line.find("COUNT") == std::string::npos)
            continue; // keep parsing.
        else
        { // we've found the data.
            // first, get the count.
            boost::algorithm::split(tokens, line, boost::algorithm::is_any_of(" "));
            unsigned fdCount = std::stoi(tokens[1]);
            descriptors.reserve(fdCount);
            // then get the starting port.
            std::getline(in, line);
            boost::algorithm::split(tokens, line, boost::algorithm::is_any_of(" "));
            unsigned portNumber = std::stoi(tokens[1]);
            // create the file descriptors.
            for (int i = 0; i < fdCount; ++i)
            {
                int fd = socket(AF_INET, SOCK_STREAM, 0);
                if (!fd)
                {
                    std::cout << "unable to create socket, continuing.\n";
                    continue;
                }
                struct sockaddr_in address;
                address.sin_family = AF_INET;
                address.sin_port = htons(portNumber);
                int addr_len = sizeof(address);
                inet_aton("127.0.0.1", &address.sin_addr);
                // binding the socket to localhost:portNumber
                if (bind(fd, (struct sockaddr *)(&address), addr_len) != 0)
                {
                    std::cout << "failed to bind socket, continuing.\n";
                    continue;
                }
                // if bind is successful, we have a good file descriptor.
                descriptors[i] = fd;
            }
        }
    }
    return std::shared_ptr<std::vector<int>>(new std::vector<int>(descriptors));
}