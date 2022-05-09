
#include "NavigationManager.hpp"

namespace gana {

NavigationManager::NavigationManager()
{}

NavigationManager::~NavigationManager()
{}

void NavigationManager::process_event(Event &evt)
{
    if (evt.cancel_pressed() && _stack.size() > 1) {
        evt.handle = true;
        navigate_up();
    }
}

void NavigationManager::navigate_up()
{
    if (_stack.size() == 1) {
        Logger::error("NavigationManager Failed to navigate up, no parent");
        return;
    }
    remove_child(_stack.top().get());
    _stack.pop();
    add_child(_stack.top().get());
}

}
