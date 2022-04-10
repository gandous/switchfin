
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <SFML/System/String.hpp>
#include "App.hpp"
#include "nanovg/src/nanovg.h"
#include "glad/glad.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg/src/nanovg_gl.h"

namespace gana {

#if SWITCH
App::App(const std::string& title):
    _mode(sf::VideoMode::getDesktopMode()),
    _window(_mode, title),
    _vg(nullptr)
#else
App::App(const std::string& title):
    _mode(1920, 1080),
    _window(_mode, title),
    _vg(nullptr)
#endif
{
    if (!gladLoadGL()) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return;
    }
    _vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    if (_vg == nullptr) {
        std::cout << "Failed to initialize nanovg context" << std::endl;
    }
    _window.setFramerateLimit(60);
}

App::~App()
{}

void App::run()
{
    while (_window.isOpen()) {
        sf::Event evt;
        while (_window.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed) {
                _window.close();
                return;
            }
        }
        nvgBeginFrame(_vg, _mode.width, _mode.height, 4);
        nvgBeginPath(_vg);
        nvgRect(_vg, 100,100, 120,30);
        nvgFillColor(_vg, nvgRGBA(255,192,0,255));
        nvgFill(_vg);
        nvgEndFrame(_vg);
        _window.display();
    }

}

}