
#include "BaseButton.hpp"
#include "type/SwitchPadButton.hpp"

namespace gana {

BaseButton::BaseButton(): _down(false)
{
    set_corner_radius(7);
    set_focusable(true);
}

BaseButton::~BaseButton()
{}

void BaseButton::process_event(Event &evt)
{
    if (evt.is_touch_down() && inside_node(evt.get_position())) {
        evt.handle = true;
        _down = true;
    } else if (_down && evt.is_touch_up()) {
        if (inside_node(evt.get_position()))
            signal_pressed.emit();
        evt.handle = true;
        _down = false;
    } else if (has_focus() && evt.accept_pressed()) {
        evt.handle = true;
        signal_pressed.emit();
    }
}

}