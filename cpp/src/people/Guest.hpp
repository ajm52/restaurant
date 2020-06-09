#ifndef GUEST_HPP
#define GUEST_HPP

#include "Person.hpp"

/**
 * Represents a restaurant guest (inherits from Person)
 * 
 * author: ajm
 * created: 1/28/20
 * last modified: 5/25/20
 **/

class Guest : public Person
{
public:
    /**
     * default Guest ctor.
     * @param id Guest id
     */
    Guest(std::string id = "DEFAULT_GID") : Person(id) {}

    /**
     * copy ctor.
     * @param g Guest to copy from.
     */
    Guest(const Guest &);

    /**
     * copy assignment operator.
     * @param g Guest to copy from.
     */
    Guest &operator=(const Guest &);

    /**
     * destructor.
     */
    ~Guest() {}

    // will eventually have methods for choosing food/drink
};

#endif // GUEST_HPP

/**
 * TODO: write the Menu class.
 * TODO: write member functions for selecting food/drink from a given Menu.
 * TODO: design the Activity class that will use Status.
 * 
 * NOTE: Can we use OOP at all here? (i.e. GuestStatus, WorkerActivity, etc)
 * */