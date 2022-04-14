
#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <SFML/Window/Event.hpp>

namespace gana {

class Event: public sf::Event {
    public:
        Event();
        ~Event();

        bool handle;
    private:
};

}

#endif /* EVENT_HPP_ */