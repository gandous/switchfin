
#include <algorithm>
#include "App.hpp"
#include "ScrollView.hpp"

namespace gana {

ScrollView::ScrollView(): _direction(ScrollDirection::XY)
{
    set_draw_propagation(false);
}

ScrollView::~ScrollView()
{}

void ScrollView::add_child(Node *node)
{
    if (_childs.size() == 0) {
        Node::add_child(node);
        node->set_left_node(get_left_node());
        node->set_top_node(get_top_node());
        node->set_right_node(get_right_node());
        node->set_bottom_node(get_bottom_node());
    } else {
        Logger::error("ScrollView cannot have more than 1 child");
    }
}

Vector2f ScrollView::get_min_size()
{
    Vector2f min_size = _min_size;

    if ((_direction & ScrollDirection::X) == 0) { // No horizontal scroll
        for (auto &child: _childs) {
            Vector2f tmp = child->get_min_size();
            min_size.x = std::max(min_size.x, _childs.front()->get_min_size().x);
        }
    }
    if ((_direction & ScrollDirection::Y) == 0) { // No vertial scroll
        if (_childs.size() > 0)
            min_size.y = std::max(min_size.y, _childs.front()->get_min_size().y);
    }
    return (min_size);
}

void ScrollView::draw(NVGcontext *ctx)
{
    nvgScissor(ctx, get_position().x, get_position().y, get_size().x, get_size().y);
    for (auto child: _childs)
        child->propagate_draw(ctx);
    nvgResetScissor(ctx);
}

void ScrollView::enter_tree()
{
    _app->signal_node_focus.connect(*this, &ScrollView::on_node_focus);
}

void ScrollView::on_focus()
{
    if (_childs.size() > 0)
        _app->set_focused_node(_childs[0]);
}

void ScrollView::on_node_focus(Node *node)
{
    if (has_child(node)) {
        float x = node != nullptr ? node->get_position().x : 0;
        gana::Logger::info("focus %f", x);
        _childs.front()->set_position(Vector2f(-x, _childs.front()->get_position().y));
    }
}

void ScrollView::set_scroll_direction(ScrollDirection direction)
{
    _direction = direction;
}

void ScrollView::set_left_node(Node *node)
{
    Node::set_left_node(node);
    for (auto &child: _childs)
        child->set_left_node(node);
}

void ScrollView::set_top_node(Node *node)
{
    Node::set_top_node(node);
    for (auto &child: _childs)
        child->set_top_node(node);
}

void ScrollView::set_right_node(Node *node)
{
    Node::set_right_node(node);
    for (auto &child: _childs)
        child->set_right_node(node);
}

void ScrollView::set_bottom_node(Node *node)
{
    Node::set_bottom_node(node);
    for (auto &child: _childs)
        child->set_bottom_node(node);
}

}
