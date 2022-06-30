
#include "SwitchPadButton.hpp"
#include "Event.hpp"

namespace gana {

Event::Event(): handle(false)
{}

Event::~Event()
{}

bool Event::is_touch() const
{
    return (is_touch_up());
}

bool Event::is_touch_up() const
{
    if ((type == sf::Event::MouseButtonReleased && mouseButton.button == sf::Mouse::Left) || type == sf::Event::TouchEnded)
        return (true);
    else
        return (false);
}

bool Event::is_touch_down() const
{
    if ((type == sf::Event::MouseButtonPressed && mouseButton.button == sf::Mouse::Left) || type == sf::Event::TouchBegan)
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

bool Event::left_pressed() const
{
    if ((type == sf::Event::KeyPressed && key.code == sf::Keyboard::Left) || (type == sf::Event::JoystickButtonReleased && (joystickButton.button == SwitchPadButton::LEFT || joystickButton.button == SwitchPadButton::STICKL_LEFT)))
        return (true);
    else
        return (false);
}

bool Event::right_pressed() const
{
    if ((type == sf::Event::KeyPressed && key.code == sf::Keyboard::Right) || (type == sf::Event::JoystickButtonReleased && (joystickButton.button == SwitchPadButton::RIGHT || joystickButton.button == SwitchPadButton::STICKL_RIGHT)))
        return (true);
    else
        return (false);
}

Vector2f Event::get_position() const
{
    if (type == sf::Event::MouseButtonPressed || type == sf::Event::MouseButtonReleased) {
        return (Vector2f(mouseButton.x, mouseButton.y));
    } else if (type == sf::Event::MouseMoved) {
        return (Vector2f(mouseMove.x, mouseMove.y));
    } else if (type == sf::Event::TouchBegan || type == sf::Event::TouchEnded || type == sf::Event::TouchMoved) {
        return (Vector2f(touch.x, touch.y));
    }
    return (Vector2f());
}

void Event::clear()
{
    handle = false;
}

}
