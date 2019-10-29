#ifndef PERSON_H
#define PERSON_H

#include <string>

class person
{
private:
    std::string id_;

public:
    explicit person::person();
    const std::string person::getId();
};
#endif //PERSON_H