
#ifndef DEBUGSCREEN_HPP_
#define DEBUGSCREEN_HPP_

#include <unordered_map>
#include <string>
#include "nanovg/src/nanovg.h"

namespace gana {

class DebugScreen {
    public:
        DebugScreen();
        ~DebugScreen();

        void draw(NVGcontext *ctx);
        void set(const std::string &key, const std::string &value);
    private:
        std::unordered_map<std::string, std::string> _values;
};

}

#endif /* DEBUGSCREEN_HPP_ */