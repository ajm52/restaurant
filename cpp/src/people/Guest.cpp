#include "Guest.hpp"

Guest::Guest(const Guest &g) : Person(g.getId()) {}

Guest &Guest::operator=(const Guest &g)
{
    if (this == &g)
        return *this;
    this->id_ = g.id_;
    return *this;
}