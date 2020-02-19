#include "Person.h"

Person::Person(const Person &p) : id_(p.id_) {}

Person &Person::operator=(const Person &p)
{
    if (this == &p)
        return *this;
    this->id_ = p.id_;
    return *this;
}