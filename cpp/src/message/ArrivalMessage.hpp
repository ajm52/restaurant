#ifndef ARRIVALMESSAGE_HPP
#define ARRIVALMESSAGE_HPP

#include "Message.hpp"
#include <string>

template <int N, const char *WID, const char *PID, const char *TID>
struct ArrivalMessage : public Message<N, WID, PID, TID>
{
    ArrivalMessage() {}
    ~ArrivalMessage() = default;
    const std::string operator()();
};
#endif // ARRIVALMESSAGE_HPP