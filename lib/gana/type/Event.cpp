
#include "SwitchPadButton.hpp"
#include "Event.hpp"

namespace gana {

Event::Event(): handle(false)
{}

Event::~Event()
{}

bool Event::is_touch() const
{
    if ((type == sf::Event::MouseButtonReleased && mouseButton.button == sf::Mouse::Left) || type == sf::Event::TouchEnded)
        return (true);
    else
        return (false);
}

bool Event::accept_pressed() const
{
    if ((type == sf::Event::KeyPressed && key.code == sf::Keyboard::Enter) || (type == sf::Event::JoystickButtonReleased && joystickButton.button == SwitchPadButton::A))
        return (true);
    else
        return (false);
}

bool Event::cancel_pressed() const
{
    if ((type == sf::Event::KeyPressed && key.code == sf::Keyboard::Escape) || (type == sf::Event::JoystickButtonReleased && joystickButton.button == SwitchPadButton::B))
        return (true);
    else
        return (false);
}

}
