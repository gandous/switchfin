
#include <sstream>
#include "duration.hpp"

static const std::size_t TICK_PER_HOUR = 36000000000;
static const std::size_t TICK_PER_MINUTE = 600000000;
static const std::size_t TICK_PER_SECOND = 10000000;
static const std::size_t MPV_TICK_PER_HOUR = 3600;
static const std::size_t MPV_TICK_PER_MINUTE = 60;

std::string tick_to_duration(Tick tick)
{
    std::ostringstream str;
    int hour = tick / TICK_PER_HOUR;
    tick = tick % TICK_PER_HOUR;
    int minute = tick / TICK_PER_MINUTE;

    if (hour > 0)
        str << hour << "h ";
    if (minute < 10)
        str << "0";
    str << minute << "m";
    return (str.str());
}

std::string mpv_tick_to_duration(uint64_t tick)
{
    std::ostringstream str;
    int hour = tick / MPV_TICK_PER_HOUR;
    tick = tick % MPV_TICK_PER_HOUR;
    int minute = tick / MPV_TICK_PER_MINUTE;
    int second = tick % MPV_TICK_PER_MINUTE;

    if (hour > 0)
        str << hour << ":";
    if (minute < 10)
        str << "0";
    str << minute << ":";
    if (second < 10)
        str << "0";
    str << second;
    return (str.str());
}