
#ifndef APP_HPP_
#define APP_HPP_

#include <string>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include "nanovg/src/nanovg.h"

namespace gana {

class App {
    public:
        App(const std::string& title);
        ~App();

        void run();
    private:
        sf::VideoMode _mode;
        sf::RenderWindow _window;
        NVGcontext* _vg;
};

}

#endif /* APP_HPP_ */