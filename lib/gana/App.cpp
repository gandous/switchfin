
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
#include "theme/color.hpp"
#include <unistd.h>

namespace gana {

#if SWITCH
App::App(const std::string& title):
    _mode(sf::VideoMode::getDesktopMode()),
    _window(_mode, title),
    _vg(nullptr),
    _root_node(nullptr),
    _focused_node(nullptr),
    _update_layout(true),
    _frame_time(0)
#else
App::App(const std::string& title):
    _mode(1280, 720),
    _window(_mode, title),
    _vg(nullptr),
    _root_node(nullptr),
    _focused_node(nullptr),
    _update_layout(true),
    _frame_time(0)
#endif
{
#if SWITCH
    socketInitializeDefault();
    nxlinkStdio();
    Result rc = romfsInit();
    if (R_FAILED(rc))
        Logger::error("Failed to init romfs");
    else
        Logger::info("romfs OK");
#endif
    if (!gladLoadGL()) {
        Logger::error("Failed to initialize OpenGL context");
        return;
    }
    _vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    if (_vg == nullptr) {
        Logger::error("Failed to initialize nanovg context");
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
    float ratio = _mode.width / _mode.height;
    Vector2f wsize = Vector2f(_mode.width, _mode.height);

    _debug.set("Size", wsize.to_string());
    while (_window.isOpen()) {
        _cl_frame_time.restart();
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
        for (auto &node: _process_node)
            node->process();
        if (_update_layout && _root_node != nullptr) {
            Logger::info("Update layout");
            _root_node->update_layout(wsize);
            _update_layout = false;
        }
        nvgBeginFrame(_vg, _mode.width, _mode.height, ratio);
        if (_root_node != nullptr)
            _root_node->propagate_draw(_vg);
        _debug.set("FPS", std::to_string(_fps_clock.get_fps()));
        _debug.set("frame time", std::to_string(_frame_time));
        _debug.draw(_vg);
        nvgEndFrame(_vg);
        _frame_time = _cl_frame_time.getElapsedTime().asMilliseconds();
        _window.display();
    }
}

void App::set_root_node(std::shared_ptr<Node> node)
{
    _root_node = node.get();
    node->propagate_enter_tree(this);
}

void App::set_root_node(Node *node)
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
    set_focused_node(node.get());
}

void App::set_focused_node(Node *node)
{
    if (_focused_node != nullptr)
        _focused_node->set_focus(false);
    if (node != nullptr)
        node->set_focus(true);
    _focused_node = node;
    node->on_focus();
    signal_node_focus.emit(node);
}

void App::add_process_node(Node *node)
{
    for (std::vector<Node*>::iterator it = _process_node.begin(); it != _process_node.end(); it++) {
        if (*it == node) {
            Logger::error("add_process_node Node already exist in process list");
            return;
        }
    }
    _process_node.push_back(node);
}

void App::remove_process_node(Node *node)
{
    for (std::vector<Node*>::iterator it = _process_node.begin(); it != _process_node.end(); it++) {
        if (*it == node) {
            _process_node.erase(it);
            return;
        }
    }
}

void App::update_layout()
{
    _update_layout = true;
}

sf::Window &App::get_window()
{
    return (_window);
}

}
