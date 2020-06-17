#ifndef MENUENTRY_HPP
#define MENUENTRY_HPP

#include <memory>
#include <string>

/**
 * @class MenuEntry
 * @description: a single entry within the restaurant's menu.
 * @author ajm
 **/
class MenuEntry
{
public:
    /**
     * @description: main constructor for MenuEntry.
     * @param name name of this entry.
     * @param preptime preparation time of this entry in minutes.
     **/
    MenuEntry(std::string name = "", unsigned prepTime = 0) : name_(name),
                                                              prepTime_(prepTime) {}

    /**
    * @description: copy constructor.
    * @param me MenuEntry to be copied.
    **/
    MenuEntry(const MenuEntry &);

    /**
    * @description: copy assignment operator.
    * @param me MenuEntry to be copied.
    * @returns this, with me's parameters.
    **/
    MenuEntry &operator=(const MenuEntry &);

    /**
     * @description: destructor.
     **/
    ~MenuEntry() = default;

    /**
     * @description: name accessor.
     * @returns this MenuEntry's name.
     **/
    inline std::string getName() const { return name_; }

    /**
     * @description: prep time accessor.
     * @returns this MenuEntry's prep time.
     **/
    inline unsigned getPrepTime() const { return prepTime_; }

private:
    std::string name_;  ///< entry name.
    unsigned prepTime_; ///< entry prep time.
};

/**
 * @description: nonmember factory function. 
 * Creates and returns a new MenuEntry managed by a smart pointer.
 * @param name name of the new entry.
 * @param type entry type.
 * @returns a constant shared pointer to a newly constructed MenuEntry.
 **/
static const std::shared_ptr<MenuEntry> makeMenuEntry(std::string, unsigned);

#endif // MENUENTRY_HPP