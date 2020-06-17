#ifndef MENU_HPP
#define MENU_HPP

#include "MenuEntryKeyComparator.hpp"
#include "MenuEntry.hpp"
#include "MenuEntryKey.hpp"
#include <map>
#include <string>

/**
 * @class Menu
 * @description: The restaurant menu, built from metadata.
 * @author ajm
 **/
class Menu
{
public:
    /**
     * @description: constructor.
     * @param opts menu selections.
     **/
    Menu(std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator> &);

    /**
     * @description: destructor.
     **/
    ~Menu() = default;

    /**
     * @description: copy constructor.
     * @param m menu being copied.
     **/
    Menu(const Menu &);

    /**
     * @description: copy assignment operator.
     * @param m menu being copied.
     * @returns a reference to this menu.
     **/
    Menu &operator=(const Menu &);

    /**
     * @description: selects a Menu option at random.
     * @param type type of entry to be randomly selected.
     * @returns name of the selected entry.
     **/
    std::string selectOption(char);

    /**
     * @description: accessor for the menu's options.
     * @returns a const reference to the menu's options.
     **/
    inline const std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator> &getOptions() const { return options_; }

    /**
     * @description: accessor for the menu's food option count.
     * @returns a count of the menu's food options.
     **/
    inline const unsigned getNumFoodOptions() const { return countOptions('F'); }

    /**
     * @description: accessor for the menu's drink option count.
     * @returns a count of the menu's drink options.
     **/
    inline const unsigned getNumDrinkOptions() const { return countOptions('D'); }

    /**
     * @description: Counts the number of options of a certain type in this menu.
     * @param type type of entries we are counting.
     * @returns the umber of menu entries of a given type.
     */
    const unsigned countOptions(char) const;

private:
    std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator> options_; ///< a table of menu options.
};

/**
 * TODO: Perhaps use typedef/alias to more explicitly format map keys?
 * 
 * NOTE: Random selection of a MenuEntry will definitely have room for optimization.
 **/

#endif // MENU_HPP