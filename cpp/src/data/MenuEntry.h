#ifndef MENUENTRY_H
#define MENUENTRY_H

#include <memory>
#include <string>

/**
 * @class <code>MenuEntry</code> : A menu entry.
 * @description: a single entry within the restaurant's menu.
 * @author ajm
 * @created: 2/5/20
 * @modified: 2/12/20
 **/
class MenuEntry
{
public:
    /**
     * @description: main constructor for <code>MenuEntry</code>.
     * @param name name of <code>this</code> entry.
     * @param preptime preparation time of <code>this</code> entry in minutes.
     **/
    MenuEntry(std::string name = "", unsigned prepTime = 0) : name_(name),
                                                              prepTime_(prepTime) {}

    /**
    * @description: <code>MenuEntry</code> copy constructor.
    * @param me <code>MenuEntry</code> to be copied.
    **/
    MenuEntry(const MenuEntry &);

    /**
    * @description: <code>MenuEntry</code> copy assignment operator.
    * @param me <code>MenuEntry</code> to be copied.
    * @returns <code>this</code>, with me's parameters.
    **/
    MenuEntry &operator=(const MenuEntry &);

    /**
     * @description: <code>MenuEntry</code> destructor.
     * Declared virtual, as I may find reason to 
     * define subclasses at a later date.
     **/
    virtual ~MenuEntry() {}

    /**
     * @description: name accessor for <code>this MenuEntry</code>.
     * @returns a copy of <code>this MenuEntry</code>'s name.
     **/
    inline std::string getName() const { return name_; }

    /**
     * @description: prep time accessor for <code>this MenuEntry</code>.
     * @returns a copy of <code>this MenuEntry</code>'s prep time.
     **/
    inline unsigned getPrepTime() const { return prepTime_; }

private:
    std::string name_;  ///< a <code>MenuEntry</code>'s name.
    unsigned prepTime_; ///< a <code>MenuEntry</code>'s prep time.
};

/**
 * @description: nonmember factory function. 
 * Creates and returns a <code>new MenuEntry</code> managed by a shared smart pointer.
 * @param name name of the new entry.
 * @param type entry type.
 * @returns a constant shared pointer to a newly constructed <code>MenuEntry</code>.
 **/
static const std::shared_ptr<MenuEntry> makeMenuEntry(std::string, unsigned);

#endif // MENUENTRY_H

/**
 * TODO: incorporate Templates (i.e. using EntryType).
 **/