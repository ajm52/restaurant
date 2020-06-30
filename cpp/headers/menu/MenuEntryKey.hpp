#ifndef MENUENTRYKEY_HPP
#define MENUENTRYKEY_HPP

#include <memory>

/**
 * @class MenuEntryKey
 * @description: the MenuEntry type and number collectively
 * identify a unique MenuEntry in a Menu. For example, a
 * cheeseburger would be identified by "F-1" if it was the
 * Menu's second food option.
 * @author ajm
 **/
class MenuEntryKey
{
public:
    /**
     * @description: constructor.
     * @param type the type identified by this key.
     * @param num the MenuEntry's number identified by this key.
     **/
    MenuEntryKey(char type = '!', unsigned num = 0) : type_(type), num_(num) {}

    /**
     * @description: copy constructor.
     * @param me to be copied.
     **/
    MenuEntryKey(const MenuEntryKey &);

    /**
     * @description: copy assignment operator.
     * @param me to be copied.
     * @returns this, with me's parameters.
     **/
    MenuEntryKey &operator=(const MenuEntryKey &);

    /**
     * @description: destructor.
     **/
    ~MenuEntryKey() = default;

    /**
     * @description: MenuEntryKey comparison function.
     * @param rhs the MenuEntryKey being compared with this MenuEntryKey.
     * @returns true if their types and numbers are equal,
     * false otherwise.
     **/
    inline const bool operator==(const MenuEntryKey &rhs) const
    {
        return (this->type_ == rhs.type_ && this->num_ == rhs.num_);
    }

    /**
     * @description: accessor for keyed MenuEntry's type.
     * @returns the type.
     **/
    inline const char getType() const { return type_; }

    /**
     * @description: accessor for keyed MenuEntry's menu number.
     * @returns the menu number.
     **/
    inline const unsigned getNum() const { return num_; }

    /**
     * @description: increments this MenuEntryKey's id number by num.
     * @param num amount to increment by.
     * @returns this object with an incremented entry number.
     **/
    MenuEntryKey &operator+=(const unsigned);

    /**
     * @description: prints MenuEntryKey's data in a concise format.
     * @param out the ostream object. 
     * @param mek MenuEntryKey's data being printed.
     * @returns the ostream object.
     **/
    friend std::ostream &operator<<(std::ostream &, const MenuEntryKey &);

private:
    char type_;    ///< keyed MenuEntry's type. For example, 'F' denotes food.
    unsigned num_; ///< keyed MenuEntry's menu number.
};

#endif // MENUENTRYKEY_HPP