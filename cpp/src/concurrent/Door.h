#ifndef DOOR_H
#define DOOR_H

#include <queue>
#include <mutex>

class Party;

/**
 * Allows entry and exit to and from the Restaurant.
 * Used by Parties and the Doorman.
 * 
 * author: ajm
 * created: 2/6/20
 * last modified: 2/12/20
 **/
class Door
{
public:
private:
    std::queue<Party *> comingIn_;
    std::queue<Party *> goingOut_;
    std::mutex mIn_;
    std::mutex mOut_;
};

#endif // DOOR_H

/**
 * NOTE: Door should not be copyable or moveable.
 * It is shared amongst guests/workers by way of
 * pointers.
 **/