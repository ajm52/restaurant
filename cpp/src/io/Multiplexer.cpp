#include "Multiplexer.h"
#include <algorithm>

void Multiplexer::resetFDs()
{
    FD_ZERO(&readfds_);
    FD_ZERO(&writefds_);
    FD_ZERO(&exceptfds_);
}

int Multiplexer::addReadSocket(int fd)
{
    if (fd < 0)
        return -1;
    readSockets_.push_back(fd);
    return 0;
}

int Multiplexer::registerReadSocket(int fd)
{
    if (fd < 0)
        return -1;
    FD_SET(fd, &readfds_);
    nfds_ = std::max(nfds_, fd);
    return 0;
}

void Multiplexer::buildSelectList()
{
    resetFDs();

    for (int &sock : readSockets_)
        FD_SET(sock, &readfds_);
    for (int &sock : writeSockets_)
        FD_SET(sock, &writefds_);
    for (int &sock : exceptSockets_)
        FD_SET(sock, &exceptfds_);
}

std::vector<int> Multiplexer::getNextActiveFDs()
{
    std::vector<int> activeFDs;
    int numFDs = select(nfds_ + 1, &readfds_, &writefds_, &exceptfds_, nullptr);
    if (numFDs <= 0)
        return activeFDs;

    // check our 3 socket lists
    for (int i = 0; i < readSockets_.size() && numFDs > 0; ++i)
    {
        if (FD_ISSET(readSockets_[i], &readfds_))
        {
            activeFDs.push_back(readSockets_[i]);
            numFDs -= 1;
        }
    }
    for (int i = 0; i < writeSockets_.size() && numFDs > 0; ++i)
    {
        if (FD_ISSET(writeSockets_[i], &writefds_))
        {
            activeFDs.push_back(writeSockets_[i]);
            numFDs -= 1;
        }
    }
    for (int i = 0; i < exceptSockets_.size() && numFDs > 0; ++i)
    {
        if (FD_ISSET(exceptSockets_[i], &exceptfds_))
        {
            activeFDs.push_back(exceptSockets_[i]);
            numFDs -= 1;
        }
    }
    return activeFDs;
}