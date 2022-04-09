
#include "App.hpp"

namespace gana {

#if SWITCH
App::App(const std::string& title): _mode(sf::VideoMode::getDesktopMode()), _window(_mode, title), _render_system(std::make_shared<RenderSystem>()), _root_node(std::make_shared<RootNode>())
#else
App::App(const std::string& title): _mode(1920, 1080), _window(_mode, title)
#endif
{
    _window.setFramerateLimit(60);
}

App::~App()
{}

void App::run()
{
    while (_window.isOpen()) {
        _window.display();
    }

}

}