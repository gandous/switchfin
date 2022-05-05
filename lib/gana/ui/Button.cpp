
#include "Button.hpp"
#include "theme/color.hpp"
#include "type/SwitchPadButton.hpp"
#include <iostream>

namespace gana {

Button::Button(): _color(128, 128, 128)
{
    set_text_align(Label::TextAlign::CENTER);
}

Button::~Button()
{}

void Button::draw(NVGcontext *ctx)
{
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, get_draw_positon().x, get_draw_positon().y, get_draw_size().x, get_draw_size().y, 7);
    nvgFillColor(ctx, _color.nvg_color());
    nvgFill(ctx);
    Label::draw(ctx);
}

void Button::process_event(Event &evt)
{
    if (evt.type == sf::Event::TouchEnded && inside_node(Vector2f(evt.touch.x, evt.touch.y))) {
        signal_pressed.emit();
    } else if (has_focus() && evt.type == sf::Event::JoystickButtonReleased && evt.joystickButton.button == SwitchPadButton::A) {
        signal_pressed.emit();
    } else if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left && inside_node(Vector2f(evt.mouseButton.x, evt.mouseButton.y))) {
        signal_pressed.emit();
    }
}

void Button::set_background_color(const Color &color)
{
    _color = color;
}

void Button::set_button_type(Type type)
{
    switch (type) {
        case PRIMARY:
        case SECONDARY:
            _color = theme::PRIMARY;
            set_font_size(20);
            break;
    }
}

}