
#ifndef LINEARGRADIENT_HPP_
#define LINEARGRADIENT_HPP_

#include "Gradient.hpp"
#include "type/Color.hpp"

namespace gana {

class LinearGradient: public Gradient {
    public:
        LinearGradient();
        ~LinearGradient();

        const NVGpaint &get_paint();
        void update_gradient(const Vector2f &position, const Vector2f &size);
    private:
        Color _icolor;
        Color _ocolor;
        NVGpaint _paint;
};

}

#endif /* LINEARGRADIENT_HPP_ */