#ifndef PARTY_H
#define PARTY_H

#include "customer.h"
#include <thread>

/* 
a party consists or one or more customers,
which is controlled by a party thread.
*/
class party
{
private:
    std::thread master;
    customer guests[];
    int numGuests;

public:
    explicit party::party(customer *folks, int n);
    customer *party::getGuests();
    int party::guestCount();
};

#endif