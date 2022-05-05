
#include "ColorRect.hpp"

namespace gana {

ColorRect::ColorRect()
{}

ColorRect::~ColorRect()
{}

void ColorRect::draw(NVGcontext *ctx)
{
    nvgBeginPath(ctx);
    nvgRect(ctx, get_draw_positon().x, get_draw_positon().y, get_draw_size().x, get_draw_size().y);
    nvgFillColor(ctx, _color.nvg_color());
    nvgFill(ctx);
}

void ColorRect::set_color(const Color &color)
{
    _color = color;
}

}