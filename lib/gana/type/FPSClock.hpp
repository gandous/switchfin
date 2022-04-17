
#ifndef FPSCLOCK_HPP_
#define FPSCLOCK_HPP_

#include <SFML/System/Clock.hpp>

namespace gana {


class FPSClock {
    public:
        FPSClock();
        ~FPSClock();

        int get_fps();
    private:
        int _last_fps;
        int _fps;
        sf::Clock _clock;
};

}

#endif /* FPSCLOCK_HPP_ */