
#include "BGRectContainer.hpp"

namespace gana {

BGRectContainer::BGRectContainer(): _color(0, 128, 255), _corner_radius(16)
{}

BGRectContainer::~BGRectContainer()
{}

void BGRectContainer::draw(NVGcontext *ctx)
{
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, get_draw_positon().x, get_draw_positon().y, get_draw_size().x, get_draw_size().y, _corner_radius);
    nvgFillColor(ctx, _color.nvg_color());
    nvgFill(ctx);
}

void BGRectContainer::set_color(const Color &color)
{
    _color = color;
}

void BGRectContainer::set_corner_radius(int radius)
{
    _corner_radius = radius;
}

}
