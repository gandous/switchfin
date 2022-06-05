
#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <SFML/Window/Event.hpp>
#include "Vector2.hpp"

namespace gana {

class Event: public sf::Event {
    public:
        Event();
        ~Event();

        bool handle;
        // Return true if the event is a left click or a touch and key is released
        bool is_touch() const;
        // Return true if the event is a left click or a touch and key is pressed
        bool is_touch_down() const;
        // Return true if the event is a left click or a touch and key is released
        bool is_touch_up() const;
        // Switch button A is pressed or Enter key pressed
        bool accept_pressed() const;
        // Switch button B is pressed or Escape key pressed
        bool cancel_pressed() const;
        Vector2f get_position() const;
        void clear();
    private:
};

}

#endif /* EVENT_HPP_ */