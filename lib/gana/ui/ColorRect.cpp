
#include "ColorRect.hpp"

namespace gana {

ColorRect::ColorRect(): _corner_radius(0)
{}

ColorRect::~ColorRect()
{}

void ColorRect::draw(NVGcontext *ctx)
{
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, get_draw_positon().x, get_draw_positon().y, get_draw_size().x, get_draw_size().y, _corner_radius);
    nvgFillColor(ctx, _color.nvg_color());
    nvgFill(ctx);
}

void ColorRect::set_color(const Color &color)
{
    _color = color;
}

void ColorRect::set_corner_radius(int radius)
{
    _corner_radius = radius;
}

}