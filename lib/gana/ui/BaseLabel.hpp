
#ifndef BASELABEL_HPP_
#define BASELABEL_HPP_

#include <string>
#include "ui/Node.hpp"
#include "type/Color.hpp"

namespace gana {

class BaseLabel: public Node {
    public:
        BaseLabel();
        ~BaseLabel();

        enum TextAlign {
            LEFT,
            CENTER,
            RIGHT
        };
        enum TextVAlign {
            TOP,
            MIDDLE,
            BOTTOM
        };

        void draw(NVGcontext *ctx) override;
        Vector2f get_min_size() override;
        void set_text(const std::string &text);
        const std::string &get_text() const;
        void set_color(const Color &color);
        void set_font_size(unsigned int size);
        void set_text_align(TextAlign align);
        void set_text_valign(TextVAlign align);
        // Maximun number of character display by the label (set to 0 to disable)
        void set_max_length(std::size_t length);
    protected:
        virtual void draw_text(NVGcontext *ctx, float x, float y) = 0;
        virtual void get_bounds(float *box) = 0;
        void apply_font(NVGcontext *ctx);
        void update_align_bitmask();
        // Return true if the min rect has changed
        bool update_min_rect();
        std::string _text;
        std::string _display_text;
        Color _color;
        unsigned int _size;
        bool _update_min_rect;
        Vector2f _min_rect;
        int _text_align;
        TextAlign _align;
        TextVAlign _valign;
        std::size_t _max_length;
};

}

#endif /* BASELABEL_HPP_ */