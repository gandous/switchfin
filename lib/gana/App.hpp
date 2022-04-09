
#ifndef APP_HPP_
#define APP_HPP_

#include <string>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace gana {

class App {
    public:
        App(const std::string& title);
        ~App();

        void run();
    private:
        sf::VideoMode _mode;
        sf::RenderWindow _window;
};

}

#endif /* APP_HPP_ */