
#ifndef GRADIENTCOLORRECT_HPP_
#define GRADIENTCOLORRECT_HPP_

#include "type/Color.hpp"
#include "Node.hpp"

namespace gana {

class GradientColorRect: public Node {
    public:
        GradientColorRect();
        ~GradientColorRect();

        void draw(NVGcontext *ctx);
        void set_size(const Vector2f &size) override;
        void set_icolor(const Color &color);
        void set_ocolor(const Color &color);
        void set_corner_radius(float radius);
    protected:
        void enter_tree();
    private:
        void update_gradient();
        NVGpaint _paint;
        Color _icolor;
        Color _ocolor;
        float _radius;
};

}

#endif /* GRADIENTCOLORRECT_HPP_ */