#ifndef MENUENTRY_H
#define MENUENTRY_H

#include <memory>
#include <string>

/**
 * @class MenuEntry : A menu entry.
 * @author ajm
 * @created: 2/5/20
 * @modified: 2/7/20
 **/
class MenuEntry
{
public:
    /**
     * @description: main constructor for MenuEntry.
     * @param name name of the new entry.
     * @param preptime preparation time, in minutes.
     **/
    MenuEntry(std::string name = "", unsigned prepTime = 0) : name_(name),
                                                              prepTime_(prepTime) {}

    /**
    * @description: MenuEntry copy constructor.
    * @param me MenuEntry to be copied.
    **/
    MenuEntry(const MenuEntry &);

    /**
    * @description: MenuEntry copy assignment operator.
    * @param me MenuEntry to be copied.
    * @returns this, with me's parameters.
    **/
    MenuEntry &operator=(const MenuEntry &);

    /**
     * @description: MenuEntry destructor.
     * Declared virtual, as I may find reason to 
     * define subclasses at a later date.
     **/
    virtual ~MenuEntry() {}

    /**
     * @description: name accessor for MenuEntries.
     * @returns a copy of this MenuEntry's name.
     **/
    inline std::string getName() const { return name_; }

private:
    std::string name_;  ///< name of the MenuEntry.
    unsigned prepTime_; ///< preparation time.

    /**
     * @description: preparation time accessor for MenuEntries.
     * @returns a copy of this MenuEntry's preparation time.
     **/
    inline unsigned getPrepTime() const { return prepTime_; }
};

/**
 * @description: nonmember factory function. 
 * Creates and returns a new MenuEntry managed by a shared smart pointer.
 * @param name name of the new entry.
 * @param type entry type.
 * @returns a constant shared pointer to a newly constructed MenuEntry.
 **/
static const std::shared_ptr<MenuEntry> makeMenuEntry(std::string, unsigned);

#endif // MENUENTRY_H

/**
 * TODO: incorporate Templates (i.e. using EntryType).
 **/