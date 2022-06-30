
#include "Timer.hpp"
#include "Logger.hpp"

namespace gana {

Timer::Timer(): _duration(0), _start(false)
{
    set_process();
}

Timer::~Timer()
{}

void Timer::restart()
{
    _start = true;
    _clock.restart();
}

void Timer::set_duration(float duration)
{
    _duration = duration;
}

void Timer::start(float duration)
{
    if (duration > 0)
        _duration = duration;
    _start = true;
    _clock.restart();
}

void Timer::process()
{
    if (_start && _clock.getElapsedTime().asSeconds() > _duration) {
        _clock.restart();
        _start = false;
        timeout.emit();
    }
}

}