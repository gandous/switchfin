
#include "Button.hpp"
#include <iostream>

namespace gana {

Button::Button(): _color(128, 128, 128)
{}

Button::~Button()
{}

void Button::draw(NVGcontext *ctx)
{
    nvgBeginPath(ctx);
    nvgRect(ctx, get_position().x, get_position().y, get_size().x, get_size().y);
    nvgFillColor(ctx, _color.nvg_color());
    nvgFill(ctx);
    Label::draw(ctx);
}

void Button::process_event(Event &evt)
{
    if (evt.type == sf::Event::TouchEnded) {
        if (inside_node(Vector2f(evt.touch.x, evt.touch.y)))
            std::cout << "Pressed" << std::endl;
    } else if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
        if (inside_node(Vector2f(evt.mouseButton.x, evt.mouseButton.y)))
            std::cout << "Pressed" << std::endl;
    }
}

}