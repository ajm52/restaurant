#include "MenuEntryKey.h"
#include "MenuEntry.h"
#include "Menu.h"

#include <cstdlib>
#include <map>
#include <string>

bool MenuEntryKeyComparator::operator()(const MenuEntryKey &lhs, const MenuEntryKey &rhs) const
{
    if (lhs.getType() == rhs.getType())
        return lhs.getNum() < rhs.getNum();
    return lhs.getType() < rhs.getType();
}

std::string Menu::selectOption(char entryType)
{
    // num calculation can be improved using a generic template approach.
    int num = entryType == 'F' ? rand() % this->getNumFoodOptions() : rand() % this->getNumDrinkOptions();
    MenuEntryKey k(entryType, num);
    return this->getOptions().at(k).getName();
}
