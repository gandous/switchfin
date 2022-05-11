
#ifndef COLORRECT_HPP_
#define COLORRECT_HPP_

#include "ui/Node.hpp"
#include "type/Color.hpp"

namespace gana {

class ColorRect: public Node {
    public:
        ColorRect();
        ~ColorRect();

        void draw(NVGcontext *ctx);
        void set_color(const Color &color);
        void set_corner_radius(int radius);
    private:
        Color _color;
        int _corner_radius;
};

}

#endif /* COLORRECT_HPP_ */