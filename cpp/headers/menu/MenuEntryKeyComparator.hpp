#ifndef MENUENTRYKEYCOMPARATOR_HPP
#define MENUENTRYKEYCOMPARATOR_HPP

#include "MenuEntryKey.hpp"

/**
 * @struct MenuEntryKeyComparator
 * @description: MenuEntryKey comparator object.
 * @note Ensures that MenuEntryKey may be used as a key in a map.
 **/
struct MenuEntryKeyComparator
{
    /**
     * @description: Comparator method.
     * @param lhs left MenuEntryKey.
     * @param rhs right MenuEntryKey.
     * @returns true if lhs appears first on the menu, false otherwise.
     **/
    bool operator()(const MenuEntryKey &lhs, const MenuEntryKey &rhs) const
    {
        if (lhs.getType() == rhs.getType())
            return lhs.getNum() < rhs.getNum();
        return lhs.getType() < rhs.getType();
    }
};
#endif // MENUENTRYKEYCOMPARATOR_HPP