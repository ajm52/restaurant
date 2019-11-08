#include "guest.h"

guest::guest(const std::string &id) : person(id), stat_(OUTSIDE) {}
guest::guest(std::string &id) : person(id), stat_(OUTSIDE) {}

const guest_status &guest::getStatus(void) const { return stat_; }