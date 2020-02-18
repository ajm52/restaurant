#ifndef MENUENTRYKEY_H
#define MENUENTRYKEY_H

#include <memory>

/**
 * @class <code>MenuEntryKey</code> : a unique <code>MenuEntry</code> identifier.
 * <p>
 * @description: the <code>MenuEntry</code> type and number collectively
 * identify a unique <code>MenuEntry</code> in a <code>Menu</code>. For example, a
 * cheeseburger would be identified by "F-1" if it was the
 * <code>Menu</code>'s second food option.
 * @author ajm
 * @created: 2/5/20
 * @modified: 2/7/20
 **/
class MenuEntryKey
{
public:
    /**
     * @description: main constructor for <code>MenuEntryKey</code>.
     * @param type the <code>MenuEntry</code>'s type identified by <code>this</code> key.
     * @param num the <code>MenuEntry</code>'s number identified by <code>this</code> key.
     **/
    MenuEntryKey(char type = '!', unsigned num = 0) : type_(type), num_(num) {}

    /**
     * @description: <code>MenuEntrykey</code> copy constructor.
     * @param me <code>MenuEntryKey</code> to be copied.
     **/
    MenuEntryKey(const MenuEntryKey &);

    /**
     * @description: <code>MenuEntryKey</code> copy assignment operator.
     * @param me to be copied.
     * @returns <code>this</code>, with me's parameters.
     **/
    MenuEntryKey &operator=(const MenuEntryKey &);

    /**
     * @description: <code>MenuEntryKey</code> destructor.
     **/
    ~MenuEntryKey() {}

    /**
     * @description: <code>MenuEntryKey</code> comparison function.
     * @param rhs the <code>MenuEntryKey</code> being compared with <b>this</b> <code>MenuEntryKey</code>.
     * @returns <code>true</code> if their types and numbers are equal,
     * <code>false</code> otherwise.
     **/
    inline bool operator==(const MenuEntryKey &rhs) const
    {
        return (this->type_ == rhs.type_ && this->num_ == rhs.num_);
    }

    /**
     * @description: accessor for keyed MenuEntry's type.
     * @returns a non-const copy of the type.
     **/
    inline char getType() const { return type_; }

    /**
     * @description: accessor for keyed <code>MenuEntry</code>'s menu number.
     * @returns a non-const copy of the menu number.
     **/
    inline unsigned getNum() const { return num_; }

    /**
     * @description: increments <code>this MenuEntryKey</code>'s id number by <code>num</code>.
     * @param num amount to increment by.
     * @returns <code></code> with a modified entry number.
     **/
    MenuEntryKey &operator+=(const unsigned);

    /**
     * @description: prints <code>MenuEntryKey</code>'s data in a concise format.
     * @param out the <code>ostream</code> object. 
     * @param mek <code>MenuEntryKey</code>'s data being printed.
     * @returns the <code>ostream</code> object.
     **/
    friend std::ostream &operator<<(std::ostream &, const MenuEntryKey &);

private:
    char type_;    ///< keyed <code>MenuEntry</code>'s type. For example, 'F' denotes food.
    unsigned num_; ///< keyed <code>MenuEntry</code>'s menu number.
};

/**
 * @description: nonmember factory function.
 * Creates and returns a <code>new MenuEntryKey</code> managed by a shared smart pointer.
 * @param type type of the keyed <code>MenuEntry</code>.
 * @param num number of the keyed <code>MenuEntry</code>.
 * @returns a <code>const</code> shared pointer to a newly constructed <code>MenuEntryKey</code>.
 **/
static const std::shared_ptr<MenuEntryKey> makeMenuEntryKey(char, unsigned);

#endif // MENUENTRYKEY_H