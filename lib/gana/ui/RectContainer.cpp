
#include "RectContainer.hpp"

namespace gana {

RectContainer::RectContainer(): _color(0, 128, 255)
{}

RectContainer::~RectContainer()
{}

void RectContainer::draw(NVGcontext *ctx)
{
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, get_position().x, get_position().y, get_size().x, get_size().y, 16);
    nvgFillColor(ctx, _color.nvg_color());
    nvgFill(ctx);
}

void RectContainer::update_layout(const Vector2f &size)
{
    Vector2f child_size = size - Vector2f(_content_margin.x + _content_margin.w, _content_margin.y + _content_margin.h);
    Vector2f child_pos = _position + Vector2f(_content_margin.x, _content_margin.y);

    set_size(size);
    for (auto &child: _childs) {
        child->get_min_size();
        child->set_position(child_pos);
        child->update_layout(child_size);
    }
}

Vector2f RectContainer::get_min_size()
{
    for (auto &child: _childs) {
        Vector2f tmp = child->get_min_size();
        _min_size.x = std::max(_min_size.x, child->get_min_size().x + _content_margin.x + _content_margin.w);
        _min_size.y = std::max(_min_size.y, child->get_min_size().y + _content_margin.y + _content_margin.h);
    }
    set_min_size(_min_size);
    return (_min_size);
}

void RectContainer::set_content_margin(const Rectf &margin)
{
    _content_margin = margin;
}

void RectContainer::set_content_margin(float margin)
{
    _content_margin.x = margin;
    _content_margin.y = margin;
    _content_margin.w = margin;
    _content_margin.h = margin;
}

void RectContainer::set_color(const Color &color)
{
    _color = color;
}

}
