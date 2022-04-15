
#include "LineEdit.hpp"
#include "switch/swkbd.hpp"
#include "Logger.hpp"

namespace gana {

LineEdit::LineEdit(): _color(128, 255, 0)
{
    set_min_size(Vector2f(50, 20));
}

LineEdit::~LineEdit()
{}

void LineEdit::draw(NVGcontext *ctx)
{
    nvgBeginPath(ctx);
    nvgRect(ctx, get_position().x, get_position().y, get_size().x, get_size().y);
    nvgFillColor(ctx, _color.nvg_color());
    nvgFill(ctx);
    Label::draw(ctx);
}

void LineEdit::process_event(Event &evt)
{
    if (evt.type == sf::Event::TouchEnded) {
#if SWITCH
        if (inside_node(Vector2f(evt.touch.x, evt.touch.y))) {
            std::string tmp = get_text();
            Logger::print(tmp);
        }
#endif
    } else if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
        if (inside_node(Vector2f(evt.mouseButton.x, evt.mouseButton.y)))
            std::cout << "Pressed" << std::endl;
    } else if (evt.type == sf::Event::TextEntered) {
        if (evt.text.unicode == 8) {
            if (_value.size() > 0) {
                _value.erase(_value.end() - 1);
                set_value(_value);
            }
        } else {
            set_value(_value + (char)evt.text.unicode);
        }
    }
}

const std::string &LineEdit::get_value() const
{
    return (_value);
}

void LineEdit::set_value(const std::string &value)
{
    _value = value;
    Label::set_text(_value);
    Logger::print(_value);
}

}
