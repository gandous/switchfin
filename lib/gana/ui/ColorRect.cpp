
#include "ColorRect.hpp"

namespace gana {

ColorRect::ColorRect()
{}

ColorRect::~ColorRect()
{}

void ColorRect::draw(NVGcontext *ctx)
{
    nvgBeginPath(ctx);
    nvgRect(ctx, get_gposition().x, get_gposition().y, get_size().x, get_size().y);
    nvgFillColor(ctx, _color.nvg_color());
    nvgFill(ctx);
}

void ColorRect::set_color(const Color &color)
{
    _color = color;
}

}