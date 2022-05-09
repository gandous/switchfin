
#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <SFML/Window/Event.hpp>

namespace gana {

class Event: public sf::Event {
    public:
        Event();
        ~Event();

        bool handle;
        // Return true if the event is a left click or a touch
        bool is_touch() const;
        // Switch button A is pressed or Enter key pressed
        bool accept_pressed() const;
        // Switch button B is pressed or Escape key pressed
        bool cancel_pressed() const;
    private:
};

}

#endif /* EVENT_HPP_ */