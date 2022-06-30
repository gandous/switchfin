
#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <SFML/System/Clock.hpp>
#include "Node.hpp"
#include "type/Signal.hpp"

namespace gana {

class Timer: public Node {
    public:
        Timer();
        ~Timer();

        void restart();
        void set_duration(float duration);
        void start(float duration = -1);
        Signal<> timeout;
    protected:
        void process() override;
    private:
        sf::Clock _clock;
        float _duration;
        bool _start;
};

}

#endif /* TIMER_HPP_ */