
#include "gana/theme/color.hpp"
#include "gana/App.hpp"
#include "Slider.hpp"

static const gana::Vector2f MIN_SIZE = gana::Vector2f(20, 20);
static const int BAR_HEIGTH = 12;

Slider::Slider(): _value(0), _max_value(0), _percentage(0), _touch_focus(false)
{
    set_min_size(MIN_SIZE);
    set_focusable(true);
}

Slider::~Slider()
{}

void Slider::draw(NVGcontext *ctx)
{
    update_percentage();
    float y = get_draw_positon().y + (get_draw_size().y - BAR_HEIGTH) / 2;
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, get_draw_positon().x, y, get_draw_size().x, BAR_HEIGTH, BAR_HEIGTH / 2);
    nvgFillColor(ctx, gana::Color(40, 40, 40, 225).nvg_color());
    nvgFill(ctx);
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, get_draw_positon().x, y, get_draw_size().x * _percentage, BAR_HEIGTH, BAR_HEIGTH / 2);
    nvgFillColor(ctx, gana::theme::PRIMARY.nvg_color());
    nvgFill(ctx);

    nvgBeginPath(ctx);
    nvgCircle(ctx, _center_sliding_point.x, _center_sliding_point.y, MIN_SIZE.y / 2);
    nvgFillColor(ctx, gana::theme::PRIMARY.nvg_color());
    nvgFill(ctx);
}

void Slider::process_event(gana::Event &evt)
{
    if (evt.is_touch_down() && evt.get_position().distance(_center_sliding_point) < MIN_SIZE.y) {
        _app->set_focused_node(this);
        evt.handle = true;
        _touch_focus = true;
    } else if (has_focus() && _touch_focus && (evt.type == sf::Event::TouchMoved || evt.type == sf::Event::MouseMoved)) {
        if (evt.get_position().x > get_draw_positon().x && evt.get_position().x < get_draw_positon().x + get_draw_size().x) {
            _percentage = (evt.get_position().x - get_draw_positon().x) / get_draw_size().x;
            _value = _max_value * _percentage;
            update_percentage();
        }
        evt.handle = true;
    } else if (has_focus() && _touch_focus && (evt.type == sf::Event::TouchEnded || evt.type == sf::Event::MouseButtonReleased)) {
        signal_value_changed.emit(_value);
        _touch_focus = false;
        _app->set_focused_node(nullptr);
    } else if (has_focus() && evt.left_pressed()) {
        _percentage -= 0.02;
        _value = _max_value * _percentage;
        update_percentage();
        evt.handle = true;
    } else if (has_focus() && evt.right_pressed()) {
        _percentage += 0.02;
        _value = _max_value * _percentage;
        update_percentage();
        evt.handle = true;
    } else if (has_focus() && evt.accept_pressed()) {
        signal_value_changed.emit(_value);
    }
}

void Slider::set_max_value(uint value)
{
    _max_value = value;
    update_percentage();
}

void Slider::set_value(uint value)
{
    if (has_focus())
        return;
    _value = value;
    update_percentage();
}

uint Slider::get_value() const
{
    return (_value);
}

void Slider::draw_outline(NVGcontext *ctx)
{
    nvgBeginPath(ctx);
    nvgCircle(ctx, _center_sliding_point.x, _center_sliding_point.y, MIN_SIZE.y / 2 + 4);
    nvgStrokeColor(ctx, gana::theme::OUTLINE_COLOR.nvg_color());
    nvgStrokeWidth(ctx, 2);
    nvgStroke(ctx);
}

void Slider::update_percentage()
{
    _percentage = (float)_value / (float)_max_value;
    _center_sliding_point.x = get_draw_positon().x + get_draw_size().x * _percentage;
    _center_sliding_point.y = get_draw_positon().y + MIN_SIZE.y / 2;
}