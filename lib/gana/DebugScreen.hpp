
#ifndef DEBUGSCREEN_HPP_
#define DEBUGSCREEN_HPP_

#include <unordered_map>
#include <string>
#include "type/Vector2.hpp"
#include "nanovg/src/nanovg.h"

namespace gana {

class DebugScreen {
    public:
        DebugScreen();
        ~DebugScreen();

        void draw(NVGcontext *ctx);
        void set(const std::string &key, const std::string &value);
    private:
        Vector2f get_bg_size(NVGcontext *ctx);
        std::unordered_map<std::string, std::string> _values;
        float _y_space;
};

}

#endif /* DEBUGSCREEN_HPP_ */