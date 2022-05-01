
#include "BGRectContainer.hpp"

namespace gana {

BGRectContainer::BGRectContainer(): _color(0, 128, 255)
{}

BGRectContainer::~BGRectContainer()
{}

void BGRectContainer::draw(NVGcontext *ctx)
{
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, get_gposition().x, get_gposition().y, get_size().x, get_size().y, 16);
    nvgFillColor(ctx, _color.nvg_color());
    nvgFill(ctx);
}

void BGRectContainer::set_color(const Color &color)
{
    _color = color;
}

}
