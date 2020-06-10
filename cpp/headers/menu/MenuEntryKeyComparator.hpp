#ifndef MENUENTRYKEYCOMPARATOR_HPP
#define MENUENTRYKEYCOMPARATOR_HPP

#include "MenuEntryKey.hpp"

/**
 * @struct <code>MenuEntryKeyComparator</code>
 * @description: <code>MenuEntryKey</code> comparator.
 * @note Ensures that <code>MenuEntryKey</code> may be used as a key in <code>std::map</code>.
 * @author ajm
 * @created: 2/10/20
 * @modified: 6/8/20
 **/
struct MenuEntryKeyComparator
{
    /**
     * @description: Comparator method.
     * @param lhs left <code>MenuEntryKey</code>.
     * @param rhs right <code>MenuEntryKey</code>.
     * @returns <code>true</code> if <code>lhs</code> appears first on the menu, <code>false</code> otherwise.
     **/
    bool operator()(const MenuEntryKey &lhs, const MenuEntryKey &rhs) const
    {
        if (lhs.getType() == rhs.getType())
            return lhs.getNum() < rhs.getNum();
        return lhs.getType() < rhs.getType();
    }
};
#endif // MENUENTRYKEYCOMPARATOR_HPP