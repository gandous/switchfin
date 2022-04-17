
#include "FPSClock.hpp"

namespace gana {

FPSClock::FPSClock(): _last_fps(0), _fps(0)
{}

FPSClock::~FPSClock()
{}

int FPSClock::get_fps()
{
    _fps++;
    if (_clock.getElapsedTime().asSeconds() >= 1.0) {
        _last_fps = _fps;
        _fps = 0;
        _clock.restart();
    }
    return (_last_fps);
}

}
