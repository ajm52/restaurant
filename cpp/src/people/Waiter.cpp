#include "Waiter.h"
#include "Table.h"
#include "Party.h"
#include <vector>
#include <mutex>

Waiter::Waiter(std::string id, int fd, std::vector<Table> &tables, Foyer &foyer)
    : Worker(fd, id),
      selector_(),
      tablespace_(tables),
      foyer_(foyer) {}

bool Waiter::registerMainFD()
{
    return selector_.addReadSocket(this->getFD()) == 0 ? true : false;
}

bool Waiter::registerPartyFD(int fd)
{
    return selector_.addReadSocket(fd) == 0 ? true : false;
}

void Waiter::seatParty(unsigned tID, Party *p)
{
    if (tID < tablespace_.size())
    {
        Table::WaiterAccess::setParty(&tablespace_[tID], p);
    }
}

void IncomingPartySlot::operator()(Waiter *w, unsigned tID)
{
    Party *p;
    {
        std::lock_guard<std::mutex> lg(w->getFoyer().m_);
        p = w->getFoyer().removeParty(tID);
    }
    w->seatParty(tID, p);
}