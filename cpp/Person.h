#ifndef PERSON_H
#define PERSON_H

#include <string>

/**
 * A base class for Guests and Workers.
 * 
 * auth: ajm
 * created: 1/21/20
 * last modified: 1/21/20
 **/
class Person
{
public:
    //ctors and copy control
    Person(const std::string id = "DEFAULT_PID") : id_(id) {}
    Person(const Person &) = delete;
    Person &operator=(const Person &) = delete;
    virtual ~Person() = default;
    //accessors
    inline const std::string &const getId() const
    {
        return id_;
    }
    inline const std::string &const getId()
    {
        return const_cast<std::string &const>(
            static_cast<const std::string &const>(id_));
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