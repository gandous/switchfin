
#ifndef APP_HPP_
#define APP_HPP_

#include <string>
#include <memory>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include "nanovg/src/nanovg.h"
#include "ui/Node.hpp"
#include "AssetManager.hpp"

namespace gana {

class App {
    public:
        App(const std::string& title);
        ~App();

        void run();
        void set_root_node(std::shared_ptr<Node> node);
        NVGcontext *get_nvg_context();
        AssetManager &get_asset_manager();
        void set_focused_node(std::shared_ptr<Node> node);
        void set_focused_node(Node *node);
    private:
        sf::VideoMode _mode;
        sf::Window _window;
        NVGcontext* _vg;
        std::shared_ptr<Node> _root_node;
        std::unique_ptr<AssetManager> _amanager;
        Node *_focused_node;
};

}

#endif /* APP_HPP_ */