#ifndef MENU_H
#define MENU_H

#include <cstdlib>
#include <map>
#include <string>

class MenuEntry;
class MenuEntryKey;

/**
 * @struct <code>MenuEntryKeyComparator</code>
 * @description: <code>MenuEntryKey</code> comparator.
 * @note Ensures that <code>MenuEntryKey</code> may be used as a key in <code>std::map</code>.
 * @author ajm
 * @created: 2/10/20
 * @modified: 2/19/20
 **/
struct MenuEntryKeyComparator
{
    /**
     * @description: Comparator method.
     * @param lhs left <code>MenuEntryKey</code>.
     * @param rhs right <code>MenuEntryKey</code>.
     * @returns <code>true</code> if <code>lhs</code> appears first on the menu, <code>false</code> otherwise.
     **/
    bool operator()(const MenuEntryKey &, const MenuEntryKey &) const;
};

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
    Menu(const std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator> &opts =
             std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator>()) : options_(opts) {}

    /**
     * @description: <code>Menu</code> destructor.
     **/
    ~Menu() {}

    /**
     * @description: deleted copy constructor.
     * The restaurant only has one <code>Menu</code>, which is shared amongst workers and guests.
     **/
    Menu(const Menu &) = delete;

    /**
     * @description: deleted copy assignment operator.
     **/
    Menu &operator=(const Menu &) = delete;

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
    const std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator> options_; ///< a table of <code>Menu</code> options.
};

/**
 * TODO: Perhaps use typedef/alias to more explicitly format map keys?
 * 
 * NOTE: Random selection of a MenuEntry will definitely have room for optimization.
 **/

#endif // MENU_H