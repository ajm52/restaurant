#include <iostream>
#include <exception>

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

struct Exception : public std::exception
{
    virtual const char *what() const throw() = 0;
};
#endif // EXCEPTION_HPP