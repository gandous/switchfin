
#ifndef MULTILINELABEL_HPP_
#define MULTILINELABEL_HPP_

#include "Label.hpp"

namespace gana {

class MultiLineLabel: public Label {
    public:
        MultiLineLabel();
        ~MultiLineLabel();
    protected:
        void draw_text(NVGcontext *ctx, float x, float y);
        void get_bounds(float *box);
};

}

#endif /* MULTILINELABEL_HPP_ */