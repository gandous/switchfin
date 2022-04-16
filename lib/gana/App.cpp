
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <SFML/System/String.hpp>
#include "App.hpp"
#include "nanovg/src/nanovg.h"
#include "glad/glad.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg/src/nanovg_gl.h"
#include "type/SwitchPadButton.hpp"
#include "type/Event.hpp"
#if SWITCH
#include <switch.h>
#endif

namespace gana {

#if SWITCH
App::App(const std::string& title):
    _mode(sf::VideoMode::getDesktopMode()),
    _window(_mode, title),
    _vg(nullptr),
    _focused_node(nullptr)
#else
App::App(const std::string& title):
    _mode(1280, 720),
    _window(_mode, title),
    _vg(nullptr),
    _focused_node(nullptr)
#endif
{
#if SWITCH
    socketInitializeDefault();
    nxlinkStdio();
    Result rc = romfsInit();
    if (R_FAILED(rc))
        std::cout << "Failed to init romfs" << std::endl;
    else
        std::cerr << "romfs OK" << std::endl;
#endif
    if (!gladLoadGL()) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return;
    }
    _vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    if (_vg == nullptr) {
        std::cout << "Failed to initialize nanovg context" << std::endl;
    }
    _amanager = std::make_unique<AssetManager>(_vg);
    _window.setFramerateLimit(60);
    _amanager->load_font("montserrat-medium", "Montserrat-Medium.ttf");;
}

App::~App()
{
#if SWITCH
    socketExit();
#endif
}

void App::run()
{
    bool refresh_ui = true;
    float ratio = _mode.width / _mode.height;
    Vector2f wsize = Vector2f(_mode.width, _mode.height);

    while (_window.isOpen()) {
        Event evt;
        while (_window.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed) {
                _window.close();
                return;
            } else if (evt.type == sf::Event::EventType::JoystickButtonPressed && evt.joystickButton.button == SwitchPadButton::PLUS) {
                _window.close();
                return;
            } else {
                _root_node->propagate_event(evt);
            }
        }
        if (refresh_ui) {
            _root_node->update_layout(wsize);
            refresh_ui = false;
        }
        nvgBeginFrame(_vg, _mode.width, _mode.height, ratio);
        _root_node->propagate_draw(_vg);
        nvgEndFrame(_vg);
        _window.display();
    }
}

void App::set_root_node(std::shared_ptr<Node> node)
{
    _root_node = node;
    node->propagate_enter_tree(this);
}

NVGcontext *App::get_nvg_context()
{
    return (_vg);
}

AssetManager &App::get_asset_manager()
{
    return (*_amanager.get());
}

void App::set_focused_node(std::shared_ptr<Node> node)
{
    if (_focused_node != nullptr)
        _focused_node->set_focus(false);
    if (node != nullptr)
        node->set_focus(true);
    _focused_node = node;
}

}