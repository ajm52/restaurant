#ifndef MENU_HPP
#define MENU_HPP

#include "MenuEntryKeyComparator.hpp"
#include "MenuEntry.hpp"
#include "MenuEntryKey.hpp"
#include <map>
#include <string>

/**
 * @class <code>Menu</code>
 * @description: The restaurant menu, built from metadata.
 * @author ajm
 * @created: 2/5/20
 * @modified: 2/19/20
 **/
class Menu
{
public:
    /**
     * @description: main constructor.
     * @param opts <code>Menu</code> selections.
     **/
    Menu(std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator> &);

    /**
     * @description: <code>Menu</code> destructor.
     **/
    ~Menu() {}

    /**
     * @description: deleted copy constructor.
     * The restaurant only has one <code>Menu</code>, which is shared amongst workers and guests.
     **/
    Menu(const Menu &);

    /**
     * @description: deleted copy assignment operator.
     **/
    Menu &operator=(const Menu &);

    /**
     * @description: selects a <code>Menu</code> option at random.
     * @param type type of entry to be randomly selected.
     * @returns name of the selected entry.
     **/
    std::string selectOption(char);

    /**
     * @description: accessor for <code>this Menu</code>'s options.
     * @returns a <code>const</code> reference to <code>this Menu</code>'s options.
     **/
    inline const std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator> &getOptions() const { return options_; }

    /**
     * @description: accessor for <code>this Menu</code>'s food option count.
     * @returns a <code>const</code> copy of <code>this Menu</code>'s food option count.
     **/
    inline const unsigned getNumFoodOptions() const { return countOptions('F'); }

    /**
     * @description: accessor for <code>this Menu</code>'s drink option count.
     * @returns a <code>const</code> copy of <code>this Menu</code>'s drink option count.
     **/
    inline const unsigned getNumDrinkOptions() const { return countOptions('D'); }

    /**
     * @description: Counts the number of options of a certain type in <code>this Menu</code>.
     * @param type type of entries we are counting.
     * @returns the umber of menu entries of a given type.
     */
    const unsigned countOptions(char) const;

private:
    std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator> options_; ///< a table of <code>Menu</code> options.
};

/**
 * TODO: Perhaps use typedef/alias to more explicitly format map keys?
 * 
 * NOTE: Random selection of a MenuEntry will definitely have room for optimization.
 **/

#endif // MENU_HPP