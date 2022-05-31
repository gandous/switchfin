
#ifndef DURATION_HPP_
#define DURATION_HPP_

#include <string>
#include "item_type.hpp"

std::string tick_to_duration(Tick tick);
std::string mpv_tick_to_duration(uint64_t tick);

#endif /* DURATION_HPP_ */