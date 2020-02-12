#ifndef MENUENTRYKEY_H
#define MENUENTRYKEY_H

#include <memory>

/**
 * @class MenuEntryKey : a unique MenuEntry identifier.
 * @description: the MenuEntry type and number collectively
 * identify a unique MenuEntry in a Menu. For example, a
 * cheeseburger would be identified by "F1" if it was the
 * Menu's second food option.
 * @author ajm
 * @created: 2/5/20
 * @modified: 2/7/20
 **/
class MenuEntryKey
{
public:
    /**
     * @description: main constructor for MenuEntryKey.
     * @param type the MenuEntry's type identified by this key.
     * @param num the MenuEntry's number identified by this key.
     **/
    MenuEntryKey(char type = '!', unsigned num = 0) : type_(type), num_(num) {}

    /**
     * @description: MenuEntrykey copy constructor.
     * @param me MenuEntryKey to be copied.
     **/
    MenuEntryKey(const MenuEntryKey &);

    /**
     * @description: MenuEntryKey copy assignment operator.
     * @param me to be copied.
     * @returns this, with me's parameters.
     **/
    MenuEntryKey &operator=(const MenuEntryKey &);

    /**
     * @description: MenuEntryKey destructor.
     **/
    ~MenuEntryKey() {}

    /**
     * @description: MenuEntryKey comparison function.
     * @param rhs the MenuEntryKey being compared with this MenuEntryKey.
     * @returns true if their types and numbers are equal,
     * false otherwise.
     **/
    inline bool operator==(const MenuEntryKey &rhs) const
    {
        return (this->type_ == rhs.type_ && this->num_ == rhs.num_);
    }

    friend std::ostream& operator<<(std::ostream&, const MenuEntryKey &);

    /**
     * @description: accessor for keyed MenuEntry's type.
     * @returns a non-const copy of the type.
     **/
    inline char getType() const { return type_; }

    /**
     * @description: accessor for keyed MenuEntry's menu number.
     * @returns a non-const copy of the menu number.
     **/
    inline unsigned getNum() const { return num_; }

private:
    char type_;    ///< the keyed MenuEntry's type (i.e. food is 'F', drink 'D', etc).
    unsigned num_; ///< the keyed MenuEntry's menu number.
};

/**
 * @description: nonmember factory function.
 * Creates and returns a new MenuEntryKey managed by a shared smart pointer.
 * @param type type of the MenuEntry being keyed on.
 * @param num number of the MenuEntry being keyed on.
 * @returns a constant shared pointer to a newly constructed MenuEntryKey.
 **/
static const std::shared_ptr<MenuEntryKey> makeMenuEntryKey(char, unsigned);

#endif // MENUENTRYKEY_H