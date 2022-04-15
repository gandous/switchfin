
#ifndef RECTCONTAINER_HPP_
#define RECTCONTAINER_HPP_

#include "Node.hpp"
#include "type/Color.hpp"
#include "type/Rect.hpp"

namespace gana {

class RectContainer: public Node {
    public:
        RectContainer();
        ~RectContainer();

        void draw(NVGcontext *ctx);
        void update_layout(const Vector2f &size) override;
        Vector2f get_min_size() override;
        void set_content_margin(const Rectf &margin);
        void set_content_margin(float margin);
        void set_color(const Color &color);
    private:
        Color _color;
        Rectf _content_margin;
};

}

#endif /* RECTCONTAINER_HPP_ */