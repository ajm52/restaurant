#include "Foyer.h"
#include <iterator>
#include <map>
#include <mutex>

bool Foyer::putParty(int id, Party *pPtr)
{
    std::lock_guard<std::mutex> lg(m_); // lock before reading/modifying
    if (table_.find(id) != table_.end())
        return false;
    table_.insert(std::pair<int, Party *>(id, pPtr));
    return true;
}

Party *Foyer::removeParty(int id)
{
    Party *ret = nullptr;
    std::lock_guard<std::mutex> lg(m_); // lock before reading/modifying
    auto itr = table_.find(id);
    if (itr != table_.end())
    {
        ret = (*itr).second;
        table_.erase(id);
    }
    //unlock
    return ret;
}