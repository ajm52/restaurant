#ifndef PERSON_H
#define PERSON_H

#include <string>

/**
 * a person may either be a guest or an employee.
 */
class person
{
private:
    const std::string id_; //identifier (ex: "S1", "G1", etc.)

public:
    person::person(std::string &id);
    person::person(const std::string &id);
    const std::string &person::getId() const;
};
#endif //PERSON_H