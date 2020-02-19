#ifndef PERSON_H
#define PERSON_H

#include <string>

/**
 * @class <code>Party</code>
 * @description: A base class for Guests and Workers.
 * @author ajm
 * @created: 1/21/20
 * @modified: 2/19/20
 **/
class Person
{
public:
    /**
     * @description: default constructor.
     * @param id <code>this Person</code>'s id string.
     */
    Person(std::string id = "DEFAULT_PID") : id_(id) {}

    /**
     * @description: copy constructor.
     * @param p <code>Person</code> to be copied.
     */
    Person(const Person &);

    /**
     * @description: copy assignment operator.
     * @param p <code>Person</code> to be copied.
     * @returns <code>this</code> as a copy of p.
     */
    Person &operator=(const Person &);

    /**
     * @description: destructor. Must be virtual for inheriting classes.
     */
    virtual ~Person() = default;

    /**
     * @description: id accessor.
     * @returns a const reference to <code>this Person</code>'s id string.
     */
    inline const std::string &getId() const
    {
        return id_;
    }

private:
    std::string id_; ///< A unique identifier. Consists of a letter and number.
};

#endif // PERSON_H

/**
 * TODO: line 19, replace 'DEFAULT_ID' with a metadata constant?
 * TODO: write a Publisher class.
 * */