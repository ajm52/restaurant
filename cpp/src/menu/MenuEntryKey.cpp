#include "MenuEntryKey.h"
#include <ostream>

MenuEntryKey::MenuEntryKey(const MenuEntryKey &mek) : type_(mek.type_), num_(mek.num_) {}

MenuEntryKey &MenuEntryKey::operator=(const MenuEntryKey &rhs)
{
    if (this == &rhs)
        return *this;
    this->type_ = rhs.type_;
    this->num_ = rhs.num_;
    return *this;
}

MenuEntryKey &MenuEntryKey::operator+=(const unsigned num)
{
    this->num_ += num;
    return *this;
}

std::ostream &operator<<(std::ostream &out, const MenuEntryKey &mek)
{
    out << mek.type_ << "-" << mek.num_;
    return out;
}

static const std::shared_ptr<MenuEntryKey> makeMenuEntryKey(char type, unsigned num)
{
    return std::shared_ptr<MenuEntryKey>(new MenuEntryKey(type, num));
}