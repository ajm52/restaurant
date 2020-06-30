#include "MenuEntry.hpp"

MenuEntry::MenuEntry(const MenuEntry &me) : name_(me.name_),
                                            prepTime_(me.prepTime_) {}

MenuEntry &MenuEntry::operator=(const MenuEntry &me)
{
    if (this == &me)
        return *this;
    this->name_ = me.name_;
    this->prepTime_ = me.prepTime_;
    return *this;
}