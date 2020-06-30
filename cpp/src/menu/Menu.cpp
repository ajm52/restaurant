#include "Menu.hpp"
#include "MenuEntry.hpp"
#include "MenuEntryKey.hpp"
#include "MenuEntryKeyComparator.hpp"
#include <map>
#include <string>

Menu::Menu(std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator> &opts)
    : options_(opts) {}

Menu::Menu(const Menu &m)
    : options_(m.options_) {}

Menu &Menu::operator=(const Menu &m)
{
    if (this == &m)
        return *this;
    options_ = m.options_;
    return *this;
}

const std::string Menu::selectOption(char entryType) const
{
    // num calculation can be improved using a generic template approach.
    int num = entryType == 'F' ? rand() % this->getNumFoodOptions() : rand() % this->getNumDrinkOptions();
    return entryType + std::to_string(num);
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