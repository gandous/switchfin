
#ifndef MULTILINELABEL_HPP_
#define MULTILINELABEL_HPP_

#include "BaseLabel.hpp"

namespace gana {

class MultiLineLabel: public BaseLabel {
    public:
        MultiLineLabel();
        ~MultiLineLabel();
    protected:
        void draw_text(NVGcontext *ctx, float x, float y);
        void get_bounds(float *box);
};

}

#endif /* MULTILINELABEL_HPP_ */