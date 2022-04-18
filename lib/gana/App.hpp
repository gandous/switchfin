
#ifndef APP_HPP_
#define APP_HPP_

#include <string>
#include <memory>
#include <unordered_map>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include "nanovg/src/nanovg.h"
#include "ui/Node.hpp"
#include "AssetManager.hpp"
#include "type/FPSClock.hpp"

namespace gana {

class App {
    public:
        App(const std::string& title);
        ~App();

        void run();
        void set_root_node(std::shared_ptr<Node> node);
        void set_root_node(Node *node);
        NVGcontext *get_nvg_context();
        AssetManager &get_asset_manager();
        void set_focused_node(std::shared_ptr<Node> node);
        void set_focused_node(Node *node);
        void add_process_node(Node *node);
        void remove_process_node(Node *node);
        void update_layout();
        sf::Window &get_window();
    private:
        sf::VideoMode _mode;
        sf::Window _window;
        NVGcontext* _vg;
        Node *_root_node;
        std::unique_ptr<AssetManager> _amanager;
        Node *_focused_node;
        std::vector<Node*> _process_node;
        bool _update_layout;
};

}

#endif /* APP_HPP_ */