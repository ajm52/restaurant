#include "MenuEntryKey.h"
#include "MenuEntry.h"
#include "Menu.h"

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

const unsigned Menu::countOptions(char type) const
{
    int count = 0;
    for (auto pair : options_)
    {
        if (pair.first.getType() == type)
            count += 1;
    }
    return count;
}