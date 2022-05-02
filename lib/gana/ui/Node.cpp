
#include "Node.hpp"
#include "theme/color.hpp"
#include "type/SwitchPadButton.hpp"
#include "App.hpp"

namespace gana {

Node::Node():
    _app(nullptr),
    _parent(nullptr),
    _layout(POSITION),
    _hsizing(SHRINK_BEGIN),
    _vsizing(SHRINK_BEGIN),
    _expand(false),
    _has_focus(false),
    _left_node(nullptr),
    _top_node(nullptr),
    _right_node(nullptr),
    _bottom_node(nullptr),
    _visibility(true),
    _draw_propagation(true),
    _process(false)
{}

Node::~Node()
{}

void Node::add_child(Node *node)
{
    if (node->_parent != nullptr) {
        std::cerr << "Child already in tree" << std::endl;
        return;
    } else if (node == this) {
        std::cerr << "You can't add a child as a child of himself" << std::endl;
        return;
    }
    _childs.push_back(node);
    node->_parent = this;
    if (_app != nullptr)
        node->propagate_enter_tree(_app);
}

void Node::remove_child(Node *node)
{
    for (std::vector<Node*>::iterator it = _childs.begin(); it != _childs.end(); it++) {
        if (*it == node) {
            (*it)->propagate_exit_tree();
            (*it)->_parent = nullptr;
            _childs.erase(it);
            return;
        }
    }
}

bool Node::has_child(const Node *node)
{
    for (auto child: _childs) {
        if (child == node)
            return (true);
        else if (child->has_child(node))
            return (true);
    }
    return (false);
}

void Node::draw(NVGcontext *ctx)
{
    (void)ctx;
}

void Node::process_event(Event &evt)
{
    (void)evt;
}

void Node::update_layout(const Vector2f &size)
{
    set_size(size);
    for (auto &child: _childs) {
        child->get_min_size();
        if (child->get_layout_mode() == Layout::ANCHOR)
            child->apply_anchor(size);
        child->update_layout(child->get_size());
    }
}

const Vector2f &Node::get_position() const
{
    return (_position);
}

void Node::set_position(const Vector2f &pos)
{
    Vector2f diff = _position - pos;

    _position = pos;
    if (_parent != nullptr)
        _global_position = _parent->_global_position + _position;
    else
        _global_position = _position;
    for (auto child: _childs)
        child->set_gposition(_global_position + child->get_position());
}

const Vector2f &Node::get_gposition() const
{
    return (_global_position);
}

void Node::set_gposition(const Vector2f &pos)
{
    Vector2f diff = _global_position - pos;

    _global_position = pos;
    if (_parent != nullptr)
        _position = _global_position - _parent->_global_position;
    else
        _position = _global_position;
    for (auto child: _childs)
        child->set_gposition(child->get_gposition() - diff);
}

const Vector2f &Node::get_size() const
{
    return (_size);
}

void Node::set_size(const Vector2f &size)
{
    _size = size;
    if (_min_size.x > _size.x)
        _size.x = _min_size.x;
    if (_min_size.y > _size.y)
        _size.y = _min_size.y;
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
    set_layout_mode(Layout::ANCHOR);
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

bool Node::inside_node(const Vector2f &pos) const
{
    if (pos.x < _global_position.x || pos.x > _global_position.x + _size.x)
        return (false);
    if (pos.y < _global_position.y || pos.y > _global_position.y + _size.y)
        return (false);
    return (true);
}

bool Node::has_focus() const
{
    return (_has_focus);
}

void Node::set_focus(bool focus)
{
    _has_focus = focus;
}

void Node::set_left_node(Node *node)
{
    _left_node = node;
}

void Node::set_up_node(Node *node)
{
    _top_node = node;
}

void Node::set_right_node(Node *node)
{
    _right_node = node;
}

void Node::set_bottom_node(Node *node)
{
    _bottom_node = node;
}

void Node::set_process(bool process)
{
    if (_app == nullptr)
        return;
    if (process)
        _app->add_process_node(this);
    else
        _app->remove_process_node(this);
    _process = process;
}

void Node::show()
{
    _visibility = true;
}

void Node::hide()
{
    _visibility = false;
}

void Node::set_visible(bool visibility)
{
    _visibility = visibility;
}

bool Node::is_visible()
{
    return (_visibility);
}

int Node::get_outline_corner_radius() const
{
    return (12);
}

void Node::draw_outline(NVGcontext *ctx)
{
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, get_gposition().x - 4, get_gposition().y - 4, get_size().x + 8, get_size().y + 8, get_outline_corner_radius());
    nvgStrokeColor(ctx, theme::OUTLINE_COLOR.nvg_color());
    nvgStrokeWidth(ctx, 2);
    nvgStroke(ctx);
}

void Node::enter_tree()
{}

void Node::exit_tree()
{}

void Node::process()
{}

void Node::on_focus()
{}

void Node::set_draw_propagation(bool prop)
{
    _draw_propagation = prop;
}

void Node::propagate_enter_tree(App *app)
{
    _app = app;
    if (_process)
        set_process(_process);
    app->update_layout();
    for (auto &child: _childs)
        child->propagate_enter_tree(app);
    enter_tree();
}

void Node::propagate_exit_tree()
{
    exit_tree();
    set_process(false);
    _app->update_layout();
    for (auto &child: _childs)
        child->propagate_exit_tree();
    _app = nullptr;
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

void Node::propagate_event(Event &evt)
{
    process_event(evt);
    if (_has_focus && (evt.type == sf::Event::JoystickButtonReleased || evt.type == sf::Event::KeyReleased))
        check_move_focus_event(evt);
    if (!evt.handle) {
        for (auto &child: _childs) {
            child->propagate_event(evt);
            if (evt.handle)
                return;
        }
    }
}

void Node::propagate_draw(NVGcontext *ctx)
{
    if (!_visibility)
        return;
    draw(ctx);
    if (_has_focus)
        draw_outline(ctx);
    if (_draw_propagation)
        for (auto &child: _childs)
            child->propagate_draw(ctx);
}

void Node::check_move_focus_event(Event &evt)
{
    int button;

    if (evt.type == sf::Event::JoystickButtonReleased)
        button = evt.joystickButton.button;
    else
        button = evt.key.code;
    switch (button) {
        case SwitchPadButton::LEFT:
        case sf::Keyboard::Left:
            if (_left_node)
                _app->set_focused_node(_left_node);
            break;
        case SwitchPadButton::UP:
        case sf::Keyboard::Up:
            if (_top_node)
                _app->set_focused_node(_top_node);
            break;
        case SwitchPadButton::RIGHT:
        case sf::Keyboard::Right:
            if (_right_node)
                _app->set_focused_node(_right_node);
            break;
        case SwitchPadButton::DOWN:
        case sf::Keyboard::Down:
            if (_bottom_node)
                _app->set_focused_node(_bottom_node);
            break;
        default:
            return;
    }
    evt.handle = true;
}

}