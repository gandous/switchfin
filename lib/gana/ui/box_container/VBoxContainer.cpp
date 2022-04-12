
#include "type/Vector2.hpp"
#include "VBoxContainer.hpp"

namespace gana {

VBoxContainer::VBoxContainer()
{
    set_size(gana::Vector2f(200, 200));
}

VBoxContainer::~VBoxContainer()
{}

void VBoxContainer::update_layout(const Vector2f &size)
{
    float y = get_position().y;
    std::size_t nb_expand = 0;
    float remaining_space = size.y - _min_size.y;

    set_size(size);
    for (auto &child: _childs)
        if (child->get_expand())
            nb_expand++;
    if (nb_expand > 0)
        remaining_space = remaining_space / nb_expand;
    for (auto &child: _childs) {
        Vector2f new_size = child->get_min_size();
        float x = _position.x;
        if (child->get_hsizing() == Node::Sizing::FILL) {
            new_size.x = size.x;
        } else if (child->get_hsizing() == Node::Sizing::SHRINK_CENTER) {
            x = _position.x + (size.x / 2) - (new_size.x / 2);
        } else if (child->get_hsizing() == Node::Sizing::SHRINK_END) {
            x = _position.x + size.x - new_size.x;
        }
        child->set_position(Vector2f(x, y));
        if (child->get_expand()) {
            new_size.y += remaining_space;
        }
        y += new_size.y;
        child->update_layout(new_size);
    }
}

Vector2f VBoxContainer::get_min_size()
{
    float w = 0;
    float h = 0;

    for (auto &child: _childs) {
        h += child->get_min_size().y;
        if (child->get_min_size().x > w)
            w = child->get_min_size().x;
    }
    set_min_size(Vector2f(w, h));
    return (_min_size);
}

}
