#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

/**
 * @class Party
 * @description: A base class for Guests and Workers.
 * @author ajm
 **/
class Person
{
public:
    /**
     * @description: constructor.
     * @param id id string.
     */
    Person(std::string id = "DEFAULT_PID") : id_(id) {}

    /**
     * @description: copy constructor.
     * @param p person to be copied.
     */
    Person(const Person &);

    /**
     * @description: copy assignment operator.
     * @param p Person to be copied.
     * @returns this person as a copy of p.
     */
    Person &operator=(const Person &);

    /**
     * @description: destructor. Must be virtual for inheriting classes.
     */
    virtual ~Person() = default;

    /**
     * @description: id accessor.
     * @returns a const reference to this person's id string.
     */
    inline const std::string &getId() const
    {
        return id_;
    }

protected:
    std::string id_; ///< A unique identifier. Consists of a letter and number.
};

#endif // PERSON_HPP

/**
 * TODO: line 19, replace 'DEFAULT_ID' with a metadata constant?
 * */