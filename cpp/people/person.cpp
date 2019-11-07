#include "person.h"

person::person(const std::string &id) : id_(id) {}
person::person(std::string &id) : id_(id) {}

const std::string &person::getId() const { return id_; }