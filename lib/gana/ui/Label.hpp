
#ifndef LABEL_HPP_
#define LABEL_HPP_

#include <string>
#include "ui/Node.hpp"
#include "ui/BaseLabel.hpp"
#include "type/Color.hpp"

namespace gana {

class Label: public BaseLabel {
    public:
        Label();
        ~Label();

        enum Preset {
            ERROR,
        };

        void set_text_valign(TextVAlign align);
        void set_preset(Preset preset);
    protected:
        virtual void draw_text(NVGcontext *ctx, float x, float y);
        virtual void get_bounds(float *box);

};

}

#endif /* LABEL_HPP_ */