#ifndef DATALOADER_H
#define DATALOADER_H

#include <memory>
#include <vector>

class Menu;

/**
 * @class <code>DataLoader</code>
 * @description: Loads simulation data from plaintext.
 * @author ajm
 * @created: 2/19/20
 * @modified: 3/4/20
 **/
class DataLoader
{
public:
    /**
     * @description: Creates the restaurant menu from metadata.
     * @returns a shared pointer to the newly created menu.
     **/
    const std::shared_ptr<Menu> createMenu();

    /**
     * @description: generic FD generator method called by other methods.
     * @param filepath where to read for file descriptor metadata.
     * @returns a shared pointer to a vector of the FDs.
     **/
    const std::shared_ptr<std::vector<int>> createFDs(std::string);
};

#endif // DATALOADER_H