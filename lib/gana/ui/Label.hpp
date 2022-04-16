
#ifndef LABEL_HPP_
#define LABEL_HPP_

#include <string>
#include "ui/Node.hpp"
#include "type/Color.hpp"

namespace gana {

class Label: public Node {
    public:
        Label();
        ~Label();

        enum TextAlign {
            LEFT,
            CENTER,
            RIGHT
        };

        void draw(NVGcontext *ctx) override;
        Vector2f get_min_size() override;
        void set_text(const std::string &text);
        void set_color(const Color &color);
        void set_font_size(unsigned int size);
        void set_text_align(TextAlign align);
    private:
        void apply_font(NVGcontext *ctx);
        std::string _text;
        Color _color;
        unsigned int _size;
        bool _update_min_rect;
        Vector2f _min_rect;
        int _text_align;
        TextAlign _align;
};

}

#endif /* LABEL_HPP_ */