#include "MenuEntry.h"

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

static const std::shared_ptr<MenuEntry> makeMenuEntry(std::string name, unsigned prepTime)
{
    return std::shared_ptr<MenuEntry>(new MenuEntry(name, prepTime));
}