#ifndef JOB_H
#define JOB_H

#include "party.h"
#include <sys/socket.h>

/**
 * A job is a struct used to contain
 * all information needed to identify
 * a waiter job.
 * 
 * Specifically, the following are needed:
 * - a reference to the party
 * - a socket to communicate with the party
 **/
struct job
{
    const party &group_;
    const int &socket_;
    job::job(const party &p, const int &s) : group_(p), socket_(s) {}
    job::job(party &p, int &s) : group_(p), socket_(s) {}
};

#endif // JOB_H