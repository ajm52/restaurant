#ifndef MENU_H
#define MENU_H

#include <cstdlib>
#include <map>
#include <string>

class MenuEntry;
class MenuEntryKey;

struct MenuEntryKeyComparator
{
    bool operator()(const MenuEntryKey &, const MenuEntryKey &) const;
};

/**
 * the restaurant menu, based on metadata.
 * 
 * author: ajm
 * created: 2/5/20
 * last modified: 2/5/20
 **/
class Menu
{
public:
    // ctor, dtor, copy control
    Menu(const std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator> &opts =
             std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator>(),
         const unsigned numF = 0, const unsigned numD = 0) : options_(opts),
                                                             numFoodOptions_(numF),
                                                             numDrinkOptions_(numD) {}
    ~Menu() {}
    Menu(const Menu &) = delete;
    Menu &operator=(const Menu &) = delete;
    // entry select funcs: both simply return a random menu selection's name, based on the provided entry type.
    std::string selectOption(char);

private:
    const std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator> options_;
    const unsigned numFoodOptions_;
    const unsigned numDrinkOptions_;
    // private accessors; Guests must only be able to select a valid option. This can be changed later, if need be.
    inline const std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator> &getOptions() const { return options_; }
    inline const unsigned getNumFoodOptions() const { return numFoodOptions_; }
    inline const unsigned getNumDrinkOptions() const { return numDrinkOptions_; }
};

/**
 * TODO: Perhaps use typedef/alias to more explicitly format map keys.
 * TODO: Would it be helpful to overload any operators for MenuEntryKey?
 **/

#endif // MENU_H