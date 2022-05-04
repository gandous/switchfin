
#include "type/Vector2.hpp"
#include "App.hpp"
#include "HBoxContainer.hpp"

namespace gana {

HBoxContainer::HBoxContainer(): _space(0)
{
    set_size(gana::Vector2f(200, 200));
}

HBoxContainer::~HBoxContainer()
{}

void HBoxContainer::add_child(Node *node)
{
    if (_childs.size() > 0) {
        _childs.back()->set_right_node(node);
        node->set_left_node(_childs.back());
    }
    Node::add_child(node);
}

void HBoxContainer::update_layout(const Vector2f &size)
{
    float x = _margin.x;
    std::size_t nb_expand = 0;
    float remaining_space = size.x - _min_size.x - (_childs.size() * _space) - _margin.x - _margin.w;

    set_size(size);
    for (auto &child: _childs)
        if (child->get_expand())
            nb_expand++;
    if (nb_expand > 0)
        remaining_space = remaining_space / nb_expand;
    for (auto &child: _childs) {
        Vector2f new_size = child->get_min_size();
        float y = _margin.y;
        if (child->get_vsizing() == Node::Sizing::FILL) {
            new_size.y = get_draw_size().y;
        } else if (child->get_vsizing() == Node::Sizing::SHRINK_CENTER) {
            y += (get_draw_size().y / 2) - (new_size.y / 2);
        } else if (child->get_vsizing() == Node::Sizing::SHRINK_END) {
            y += get_draw_size().y - new_size.y;
        }
        if (child->get_expand())
            new_size.x += remaining_space;
        child->set_position(Vector2f(x, y));
        x += new_size.x + _space;
        child->update_layout(new_size);
    }
}

Vector2f HBoxContainer::get_min_size()
{
    float w = 0;
    float h = 0;

    for (auto &child: _childs) {
        w += child->get_min_size().x;
        if (child->get_min_size().y > h)
            h = child->get_min_size().y;
    }
    w += (_childs.size() - 1) * _space;
    set_min_size(Vector2f(w, h));
    return (_min_size);
}

void HBoxContainer::add_spacer(float w, bool expand)
{
    Node *spacer = make_managed<Node>();
    spacer->set_min_size(Vector2f(0, w));
    if (expand)
        spacer->set_expand();
    add_child(spacer);
}

void HBoxContainer::set_space(float space)
{
    _space = space;
}

void HBoxContainer::on_focus()
{
    if (_childs.size() > 0)
        _app->set_focused_node(_childs.front());
}

}
