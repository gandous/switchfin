
#ifndef COLOR_HPP_
#define COLOR_HPP_

#include "nanovg/src/nanovg.h"

namespace gana {

class Color {
    public:
        Color();
        Color(int r, int g, int b, int a);
        Color(int r, int g, int b);
        ~Color();

        NVGcolor nvg_color() const;
        int r;
        int g;
        int b;
        int a;
    private:
};

}

#endif /* COLOR_HPP_ */