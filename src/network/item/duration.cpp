
#include <sstream>
#include "duration.hpp"

static const std::size_t TICK_PER_HOUR = 36000000000;
static const std::size_t TICK_PER_MINUTE = 600000000;
static const std::size_t TICK_PER_SECOND = 10000000;

std::string tick_to_duration(Tick tick)
{
    std::ostringstream str;
    int hour = tick / TICK_PER_HOUR;
    int minute = tick / TICK_PER_MINUTE;

    if (hour > 0) {
        str << hour << "h ";
    }
    str << minute << "m";
    return (str.str());
}
