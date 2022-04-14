
#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "ui/Label.hpp"

namespace gana {

class Button: public Label {
    public:
        Button();
        ~Button();

        void draw(NVGcontext *ctx) override;
        void process_event(Event &evt) override;
    private:
        Color _color;
};

}

#endif /* BUTTON_HPP_ */