
#include "Label.hpp"
#include "App.hpp"
#include "theme/color.hpp"

namespace gana {

Label::Label()
{
    _valign = TextVAlign::MIDDLE;
    update_align_bitmask();
}

Label::~Label()
{}

void Label::set_text_valign(TextVAlign align)
{
    _valign = align;
    update_align_bitmask();
}

void Label::set_preset(Preset preset)
{
    switch (preset) {
        case Preset::ERROR:
            set_color(theme::TEXT_COLOR_ERROR);
        default:
            break;
    }
}

void Label::draw_text(NVGcontext *ctx, float x, float y)
{
    nvgText(ctx, x, y, _text.c_str(), NULL);
}

void Label::get_bounds(float *box)
{
    nvgTextBounds(_app->get_nvg_context(), 0, 0, _text.c_str(), NULL, box);
}

}
