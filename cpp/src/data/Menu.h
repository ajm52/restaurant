#ifndef MENU_H
#define MENU_H

#include <cstdlib>
#include <map>
#include <string>

class MenuEntry;
class MenuEntryKey;

/**
 * @struct <code>MenuEntryKeyComparator</code> : <code>MenuEntryKey</code> comparator.
 * @description: Ensures that <code>MenuEntryKey</code> may be used as a key in <code>std::map</code>.
 * @author ajm
 * @created: 2/10/20
 * @modified: 2/12/20
 **/
struct MenuEntryKeyComparator
{
    /**
     * @description: <code>MenuEntryKey</code> comparator method.
     * @param lhs left <code>MenuEntryKey</code>.
     * @param rhs right <code>MenuEntryKey</code>.
     * @returns <code>true</code> if <code>lhs</code> appears first on the menu, <code>false</code> otherwise.
     **/
    bool operator()(const MenuEntryKey &, const MenuEntryKey &) const;
};

/**
 * @class Menu : The restaurant menu, built on metadata.
 * @author ajm
 * @created: 2/5/20
 * @modified: 2/12/20
 **/
class Menu
{
public:
    /**
     * @description: main constructor for Menu.
     * @param opts <code>Menu</code> selections.
     * @param numF food option count.
     * @param numD drink option count.
     **/
    Menu(const std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator> &opts =
             std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator>(),
         const unsigned numF = 0, const unsigned numD = 0) : options_(opts),
                                                             numFoodOptions_(numF),
                                                             numDrinkOptions_(numD) {}

    /**
     * @description: <code>Menu</code> destructor.
     **/
    ~Menu() {}

    /**
     * @description: deleted <code>Menu</code> copy constructor.
     * <p>The restaurant only has one <code>Menu</code>, which is shared amongst workers and guests.
     **/
    Menu(const Menu &) = delete;

    /**
     * @description: deleted <code>Menu</code> copy assignment operator.
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
    inline const unsigned getNumFoodOptions() const { return numFoodOptions_; }

    /**
     * @description: accessor for <code>this Menu</code>'s drink option count.
     * @returns a <code>const</code> copy of <code>this Menu</code>'s drink option count.
     **/
    inline const unsigned getNumDrinkOptions() const { return numDrinkOptions_; }

private:
    const std::map<MenuEntryKey, MenuEntry, MenuEntryKeyComparator> options_; ///< a table of <code>Menu</code> options.
    const unsigned numFoodOptions_;                                           ///< <code>this Menu</code>'s food option count.
    const unsigned numDrinkOptions_;                                          ///< <code>this Menu</code>'s drink option count.
};

/**
 * TODO: Perhaps use typedef/alias to more explicitly format map keys.
 * NOTE: Would it be helpful to overload any operators for MenuEntryKey?
 **/

#endif // MENU_H