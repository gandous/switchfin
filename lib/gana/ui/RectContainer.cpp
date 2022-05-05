
#include "RectContainer.hpp"

namespace gana {

RectContainer::RectContainer()
{}

RectContainer::~RectContainer()
{}

void RectContainer::update_layout(const Vector2f &size)
{
    Vector2f child_size = size - Vector2f(_content_margin.x + _content_margin.w + _margin.x + _margin.w, _content_margin.y + _content_margin.h + _margin.y + _margin.h);
    Vector2f child_pos = Vector2f(_content_margin.x + _margin.x, _content_margin.y + _margin.y);

    set_size(size);
    for (auto &child: _childs) {
        child->get_min_size();
        child->set_position(child_pos);
        child->update_layout(child_size);
    }
}

Vector2f RectContainer::get_min_size()
{
    float x = _real_min_size.x;
    float y = _real_min_size.y;

    for (auto &child: _childs) {
        Vector2f tmp = child->get_min_size();
        x = std::max(x, tmp.x + _content_margin.x);
        y = std::max(y, tmp.y + _content_margin.y);
    }
    set_min_size(Vector2f(x - _margin.x - _margin.w, y - _margin.y - _margin.h));
    return (_real_min_size);
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

}
