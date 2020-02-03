#ifndef PERSON_H
#define PERSON_H

#include <string>

/**
 * A base class for Guests and Workers.
 * 
 * author: ajm
 * created: 1/21/20
 * last modified: 1/29/20
 **/
class Person
{
public:
    // ctors and copy control
    Person(std::string id = "DEFAULT_PID") : id_(id) {}
    Person(const Person &) = delete;
    Person &operator=(const Person &) = delete;
    virtual ~Person() = default;
    // accessors
    inline const std::string &getId() const
    {
        return id_;
    }
    inline const std::string &getId()
    {
        return static_cast<const Person &>(*this).getId();
    }

private:
    const std::string id_;
};

#endif // PERSON_H

/**
 * TODO: line 19, replace 'DEFAULT_ID' with a metadata constant.
 * TODO: write a Publisher interface.
 * 
 * NOTE: func on line 29 may need revision for proper casting.
 * */