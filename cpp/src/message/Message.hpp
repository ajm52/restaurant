#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <tuple>
#include <string>

/**
 * @class Message
 * @description: Abstract information cradle for communication between threads.
 * @author ajm
 * @created: 3/5/20
 * @modified: 3/5/20
 */
template <int N, const char *... ARGS>
struct Message
{
    Message() {}
    virtual ~Message() = default;
    virtual const std::string operator()() = 0;
};

#endif // MESSAGE_HPP