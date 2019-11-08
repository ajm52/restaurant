#ifndef GUEST_H
#define GUEST_H

#include "person.h"
#include "../data/guest_status.h"

/**
 * subclass of person. 
 **/
class guest : public person
{
private:
    guest_status stat_; //shouldn't ever be modified, except by party, a friend of guest.

public:
    guest::guest(std::string &id);
    guest::guest(const std::string &id);
    const guest_status &getStatus(void) const;
};

#endif //GUEST_H