#include "Waiter.h"

bool Waiter::registerMainFD()
{
    return selector_.addReadSocket(this->getFD()) == 0 ? true : false;
}

bool Waiter::registerPartyFD(int fd)
{
    return selector_.addReadSocket(fd) == 0 ? true : false;
}
