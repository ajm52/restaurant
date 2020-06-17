#ifndef GUEST_HPP
#define GUEST_HPP

#include "Person.hpp"

/**
 * @class Guest
 * @description: Represents a restaurant guest (inherits from Person)
 * @author ajm
 **/

class Guest : public Person
{
public:
    /**
     * @description: constructor.
     * @param id guest id
     */
    Guest(std::string id = "DEFAULT_GID") : Person(id) {}

    /**
     * @description: copy constructor.
     * @param g guest to copy from.
     */
    Guest(const Guest &);

    /**
     * @description: copy assignment operator.
     * @param g guest to copy from.
     * @returns a reference to this guest.
     */
    Guest &operator=(const Guest &);

    /**
     * @description: destructor.
     */
    ~Guest() = default;

    // will eventually have methods for choosing food/drink
};

#endif // GUEST_HPP

/**
 * TODO: write member functions for selecting food/drink from a given Menu.
 **/