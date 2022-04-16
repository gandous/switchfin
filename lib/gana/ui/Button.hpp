
#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "ui/Label.hpp"

namespace gana {

class Button: public Label {
    public:
        Button();
        ~Button();

        enum Type {
            PRIMARY,
            SECONDARY
        };

        void draw(NVGcontext *ctx) override;
        void process_event(Event &evt) override;
        void set_background_color(const Color &color);
        void set_button_type(Type type);
    private:
        Color _color;
};

}

#endif /* BUTTON_HPP_ */