
#include "type/Vector2.hpp"
#include "App.hpp"
#include "VBoxContainer.hpp"

namespace gana {

VBoxContainer::VBoxContainer()
{
    set_size(gana::Vector2f(200, 200));
}

VBoxContainer::~VBoxContainer()
{}

void VBoxContainer::add_child(Node *node)
{
    if (_childs.size() > 0) {
        _childs.back()->set_bottom_node(node);
        node->set_top_node(_childs.back());
    }
    Node::add_child(node);
    node->set_left_node(get_left_node());
    node->set_right_node(get_right_node());
}

void VBoxContainer::update_layout(const Vector2f &size)
{
    float y = _margin.h;
    std::size_t nb_expand = 0;
    float remaining_space = size.y - _min_size.y - (_childs.size() * _space) - _margin.y - _margin.h;

    set_size(size);
    for (auto &child: _childs)
        if (child->get_expand())
            nb_expand++;
    if (nb_expand > 0)
        remaining_space = remaining_space / nb_expand;
    for (auto &child: _childs) {
        Vector2f new_size = child->get_min_size();
        float x = _margin.x;
        if (child->get_hsizing() == Node::Sizing::FILL) {
            new_size.x = get_draw_size().x;
        } else if (child->get_hsizing() == Node::Sizing::SHRINK_CENTER) {
            x += (get_draw_size().x / 2) - (new_size.x / 2);
        } else if (child->get_hsizing() == Node::Sizing::SHRINK_END) {
            x += get_draw_size().x - new_size.x;
        }
        if (child->get_expand())
            new_size.y += remaining_space;
        child->set_position(Vector2f(x, y));
        child->update_layout(new_size);
        y += new_size.y + _space;
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
    h += (_childs.size() * _space);
    set_min_size(Vector2f(w, h));
    return (_min_size);
}

void VBoxContainer::add_spacer(float h, bool expand)
{
    Node *spacer = make_managed<Node>();
    spacer->set_min_size(Vector2f(0, h));
    if (expand)
        spacer->set_expand();
    add_child(spacer);
}

void VBoxContainer::set_space(float space)
{
    _space = space;
}


void VBoxContainer::on_focus()
{
    if (_childs.size() > 0)
        _app->set_focused_node(_childs.front());
}

void VBoxContainer::set_left_node(Node *node)
{
    Node::set_left_node(node);
    for (auto &child: _childs)
        child->set_left_node(node);
}

void VBoxContainer::set_right_node(Node *node)
{
    Node::set_right_node(node);
    for (auto &child: _childs)
        child->set_right_node(node);
}

}
