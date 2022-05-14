
#include <algorithm>
#include "App.hpp"
#include "ScrollView.hpp"

#define X_SCROLL ((_direction & ScrollDirection::X) != 0)
#define Y_SCROLL ((_direction & ScrollDirection::Y) != 0)

namespace gana {

ScrollView::ScrollView(): _direction(ScrollDirection::XY)
{
    set_draw_propagation(false);
}

ScrollView::~ScrollView()
{}

void ScrollView::update_layout(const Vector2f &size)
{
    set_size(size);
    for (auto &child: _childs) {
        child->get_min_size();
        child->update_layout(child->get_expand() ? size : child->get_size());
    }
}

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

bool ScrollView::has_child(const Node *node)
{
    (void)node;
    return (false);
}

Vector2f ScrollView::get_min_size()
{
    Vector2f min_size = _min_size;

    if (!X_SCROLL) {
        if (_childs.size() > 0)
            min_size.x = std::max(min_size.x, _childs.front()->get_min_size().x);
    }
    if (!Y_SCROLL) {
        if (_childs.size() > 0)
            min_size.y = std::max(min_size.x, _childs.front()->get_min_size().y);
    }
    return (min_size);
}

void ScrollView::draw(NVGcontext *ctx)
{
    nvgScissor(ctx, get_draw_positon().x, get_draw_positon().y, get_draw_size().x, get_draw_size().y);
    for (auto child: _childs)
        child->propagate_draw(ctx);
    nvgResetScissor(ctx);
}

void ScrollView::enter_tree()
{
    _app->signal_node_focus.connect(*this, &ScrollView::on_node_focus);
}

void ScrollView::exit_tree()
{
    _app->signal_node_focus.disconnect(*this);
}

void ScrollView::on_focus()
{
    if (_childs.size() > 0)
        _app->set_focused_node(_childs[0]);
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

void ScrollView::on_node_focus(Node *node)
{
    if (Node::has_child(node)) {
        float x = X_SCROLL ? node->get_position().x : 0;
        float y = Y_SCROLL ? node->get_position().y : 0;
        gana::Logger::info("focus %.3f %.3f", x, y);
        _childs.front()->set_position(Vector2f(-x, -y));
    }
}

}
