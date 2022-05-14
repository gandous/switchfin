
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
    std::shared_ptr<gana::Node> _old = _stack.top();
    remove_child(_old.get());
    _stack.pop();
    add_child(_stack.top().get());
}

}
