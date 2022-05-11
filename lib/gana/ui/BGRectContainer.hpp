
#ifndef BGRECTCONTAINER_HPP_
#define BGRECTCONTAINER_HPP_

#include "Node.hpp"
#include "type/Color.hpp"
#include "type/Rect.hpp"
#include "RectContainer.hpp"

namespace gana {

class BGRectContainer: public RectContainer {
    public:
        BGRectContainer();
        ~BGRectContainer();

        void draw(NVGcontext *ctx);
        void set_color(const Color &color);
        void set_corner_radius(int radius);
    private:
        Color _color;
        int _corner_radius;
};

}

#endif /* BGRECTCONTAINER_HPP_ */