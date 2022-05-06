
#ifndef GRADIENT_HPP_
#define GRADIENT_HPP_

#include "nanovg/src/nanovg.h"
#include "type/Vector2.hpp"

namespace gana {

class Gradient {
    public:
        virtual ~Gradient() = default;

        virtual const NVGpaint &get_paint() = 0;
        virtual void update_gradient(const Vector2f &position, const Vector2f &size) = 0;

    private:
};

}

#endif /* GRADIENT_HPP_ */