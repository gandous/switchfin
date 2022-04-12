
#ifndef APP_HPP_
#define APP_HPP_

#include <string>
#include <memory>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include "nanovg/src/nanovg.h"
#include "ui/Node.hpp"

namespace gana {

class App {
    public:
        App(const std::string& title);
        ~App();

        void run();
        void set_root_node(std::shared_ptr<Node> node);
    private:
        sf::VideoMode _mode;
        sf::RenderWindow _window;
        NVGcontext* _vg;
        std::shared_ptr<Node> _root_node;
};

}

#endif /* APP_HPP_ */