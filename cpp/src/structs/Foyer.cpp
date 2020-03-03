#include "Foyer.h"
#include <iterator>
#include <map>

bool Foyer::putParty(int id, Party *pPtr)
{
    if (table_.find(id) != table_.end())
        return false;
    //lock
    table_.insert(std::pair<int, Party *>(id, pPtr));
    //unlock
    return true;
}

Party *Foyer::removeParty(int id)
{
    Party *ret = nullptr;
    //lock
    auto itr = table_.find(id);
    if (itr != table_.end())
    {
        ret = (*itr).second;
        table_.erase(id);
    }
    //unlock
    return ret;
}