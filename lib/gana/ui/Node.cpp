
#include "Node.hpp"
#include <iostream>

namespace gana {

Node::Node(): _app(nullptr), _layout(POSITION), _hsizing(SHRINK_BEGIN), _vsizing(SHRINK_BEGIN), _expand(false)
{}

Node::~Node()
{}

void Node::add_child(const std::shared_ptr<Node> &node)
{
    _childs.push_back(node);
    if (_app != nullptr)
        node->enter_tree(_app);
}

void Node::draw(NVGcontext *ctx)
{
    for (auto &child: _childs)
        child->draw(ctx);
}

void Node::update_layout(const Vector2f &size)
{
    set_size(size);
    for (auto &child: _childs) {
        child->get_min_size();
        if (child->get_layout_mode() == Layout::POSITION) {
            child->update_layout(child->get_size());
        } else {
            child->apply_anchor(size);
        }
    }
}

const Vector2f &Node::get_position() const
{
    return (_position);
}

void Node::set_position(const Vector2f &pos)
{
    _position = pos;
}

const Vector2f &Node::get_size() const
{
    return (_size);
}

void Node::set_size(const Vector2f &size)
{
    _size = size;
}

Vector2f Node::get_min_size()
{
    return (_min_size);
}

void Node::set_min_size(const Vector2f &min_size)
{
    _min_size = min_size;
    if (_min_size.x > _size.x)
        _size.x = _min_size.x;
    if (_min_size.y > _size.y)
        _size.y = _min_size.y;
}

Node::Sizing Node::get_hsizing() const
{
    return (_hsizing);
}

void Node::set_hsizing(Node::Sizing sizing)
{
    _hsizing = sizing;
}

Node::Sizing Node::get_vsizing() const
{
    return (_vsizing);
}

void Node::set_vsizing(Node::Sizing sizing)
{
    _vsizing = sizing;
}

bool Node::get_expand() const
{
    return (_expand);
}

void Node::set_expand(bool expand)
{
    _expand = expand;
}

Node::Layout Node::get_layout_mode() const
{
    return (_layout);
}

void Node::set_layout_mode(Node::Layout mode)
{
    _layout = mode;
}

const Rectf &Node::get_anchor() const
{
    return (_anchor);
}

void Node::set_anchor(const Rectf &anchor)
{
    _anchor = anchor;
}

void Node::set_anchor(Anchor anchor)
{
    switch (anchor) {
        case TOP_LEFT:
            set_anchor(Rectf(0, 0, 0, 0));
            set_xgrow_direction(GrowDirection::END);
            set_ygrow_direction(GrowDirection::END);
            break;
        case TOP_RIGHT:
            set_anchor(Rectf(1, 0, 1, 0));
            set_xgrow_direction(GrowDirection::BEGIN);
            set_ygrow_direction(GrowDirection::END);
            break;
        case BOTTOM_LEFT:
            set_anchor(Rectf(0, 1, 0, 1));
            set_xgrow_direction(GrowDirection::END);
            set_ygrow_direction(GrowDirection::BEGIN);
            break;
        case BOTTOM_RIGHT:
            set_anchor(Rectf(1, 1, 1, 1));
            set_xgrow_direction(GrowDirection::BEGIN);
            set_ygrow_direction(GrowDirection::BEGIN);
            break;
        case CENTER_LEFT:
            set_anchor(Rectf(0, 0.5, 0, 0.5));
            set_xgrow_direction(GrowDirection::END);
            set_ygrow_direction(GrowDirection::BOTH);
            break;
        case CENTER_TOP:
            set_anchor(Rectf(0.5, 0, 0.5, 0));
            set_xgrow_direction(GrowDirection::BOTH);
            set_ygrow_direction(GrowDirection::END);
            break;
        case CENTER_RIGHT:
            set_anchor(Rectf(1, 0.5, 1, 0.5));
            set_xgrow_direction(GrowDirection::BEGIN);
            set_ygrow_direction(GrowDirection::BOTH);
            break;
        case CENTER_BOTTOM:
            set_anchor(Rectf(0.5, 1, 0.5, 1));
            set_xgrow_direction(GrowDirection::BOTH);
            set_ygrow_direction(GrowDirection::BEGIN);
            break;
        case LEFT_WIDE:
            set_anchor(Rectf(0, 0, 0, 1));
            set_xgrow_direction(GrowDirection::END);
            set_ygrow_direction(GrowDirection::BOTH);
            break;
        case TOP_WIDE:
            set_anchor(Rectf(0, 0, 1, 0));
            set_xgrow_direction(GrowDirection::BOTH);
            set_ygrow_direction(GrowDirection::END);
            break;
        case RIGHT_WIDE:
            set_anchor(Rectf(1, 0, 1, 1));
            set_xgrow_direction(GrowDirection::BEGIN);
            set_ygrow_direction(GrowDirection::BOTH);
            break;
        case BOTTOM_WIDE:
            set_anchor(Rectf(0, 1, 1, 1));
            set_xgrow_direction(GrowDirection::BOTH);
            set_ygrow_direction(GrowDirection::BEGIN);
            break;
        case CENTER:
            set_anchor(Rectf(0.5, 0.5, 0.5, 0.5));
            set_xgrow_direction(GrowDirection::BOTH);
            set_ygrow_direction(GrowDirection::BOTH);
            break;
        case FULL_RECT:
            set_anchor(Rectf(0, 0, 1, 1));
            set_xgrow_direction(GrowDirection::BEGIN);
            set_ygrow_direction(GrowDirection::BEGIN);
            break;
        default:
            std::cout << "default" << std::endl;
            break;
    }
}

void Node::set_xgrow_direction(Node::GrowDirection direction)
{
    _hdirection = direction;
}

void Node::set_ygrow_direction(Node::GrowDirection direction)
{
    _vdirection = direction;
}

void Node::enter_tree(App *app)
{
    _app = app;
    for (auto &child: _childs)
        child->enter_tree(app);
}

void Node::apply_anchor(const Vector2f &size)
{
    Vector2f top_left = Vector2f(size.x * _anchor.x, size.y * _anchor.y);
    Vector2f bottom_right = Vector2f(size.x * _anchor.w, size.y * _anchor.h);
    Vector2f new_size = bottom_right - top_left;


    if (new_size.x < _min_size.x) {
        if (_hdirection == BEGIN) {
            float diff = _min_size.x - new_size.x;
            new_size.x = _min_size.x;
            top_left.x -= diff;
        } else if (_hdirection == END) {
            new_size.x = _min_size.x;
        } else {
            float diff = (_min_size.x - new_size.x) / 2;
            top_left.x -= diff;
            new_size.x = _min_size.x;
        }
    }
    if (new_size.y < _min_size.y) {
        if (_vdirection == BEGIN) {
            float diff = _min_size.y - new_size.y;
            new_size.y = _min_size.y;
            top_left.y -= diff;
        } else if (_vdirection == END) {
            new_size.y = _min_size.y;
        } else {
            float diff = (_min_size.y - new_size.y) / 2;
            top_left.y -= diff;
            new_size.y = _min_size.y;
        }
    }
    set_position(top_left);
    set_size(new_size);
}

}