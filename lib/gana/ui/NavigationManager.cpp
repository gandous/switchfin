
#include "NavigationManager.hpp"

namespace gana {

NavigationManager::NavigationManager()
{}

NavigationManager::~NavigationManager()
{}

void NavigationManager::process_event(Event &evt)
{
    if (evt.cancel_pressed() && _stack.size() > 1) {
        navigate_up();
        evt.handle = true;
    }
}

void NavigationManager::navigate_up()
{
    if (_stack.size() == 1) {
        Logger::error("NavigationManager Failed to navigate up, no parent");
        return;
    }
    NavPage old = _stack.top();
    remove_child(old.node.get());
    _stack.pop();
    NavPage news = _stack.top();
    add_child(news.node.get());
    _app->set_focused_node(old.focus_node);
}

}
