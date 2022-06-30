
#include "BaseButton.hpp"
#include "type/SwitchPadButton.hpp"

namespace gana {

BaseButton::BaseButton()
{
    set_corner_radius(7);
    set_focusable(true);
}

BaseButton::~BaseButton()
{}

void BaseButton::process_event(Event &evt)
{
    if (evt.is_touch() && inside_node(Vector2f(evt.touch.x, evt.touch.y))) {
        evt.handle = true;
        signal_pressed.emit();
    } else if (has_focus() && evt.accept_pressed()) {
        evt.handle = true;
        signal_pressed.emit();
    }
}

}