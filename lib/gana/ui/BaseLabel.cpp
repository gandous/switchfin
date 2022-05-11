
#include "BaseLabel.hpp"
#include "App.hpp"
#include "theme/color.hpp"

namespace gana {

BaseLabel::BaseLabel():
    _color(theme::TEXT_COLOR_W),
    _size(20),
    _update_min_rect(true),
    _text_align(NVG_ALIGN_TOP | NVG_ALIGN_LEFT),
    _align(LEFT),
    _valign(TOP),
    _max_length(0)
{}

BaseLabel::~BaseLabel()
{}

void BaseLabel::draw(NVGcontext *ctx)
{
    float x = get_draw_positon().x;
    float y = get_draw_positon().y;

    if (_align == TextAlign::CENTER)
        x += get_draw_size().x / 2;
    else if (_align == TextAlign::RIGHT)
        x += get_draw_size().x;
    if (_valign == TextVAlign::MIDDLE)
        y += get_draw_size().y / 2;
    else if (_valign == TextVAlign::BOTTOM)
        y += get_draw_size().y;
    nvgBeginPath(ctx);
    apply_font(ctx);
    draw_text(ctx, x, y);
}

Vector2f BaseLabel::get_min_size()
{
    if (_app == nullptr)
        return (Vector2f());
    if (_update_min_rect) {
        apply_font(_app->get_nvg_context());
        float box[4] = {0, 0, 0, 0};
        nvgTextAlign(_app->get_nvg_context(), NVG_ALIGN_TOP);
        get_bounds(box);
        _min_rect.x = std::max(box[2], Node::get_min_size().x);
        _min_rect.y = std::max(box[3], Node::get_min_size().y);
        _update_min_rect = false;
    }
    return (_min_rect);
}

void BaseLabel::set_text(const std::string &text)
{
    _display_text = text;
    _text = text;
    if (_max_length != 0 && text.size() > _max_length) {
        _display_text.resize(_max_length);
        for (std::string::iterator it = _display_text.end() - 3; it != _display_text.end(); it++)
            *it = '.';
    }
    _update_min_rect = true;
    if (_app != nullptr)
        _app->update_layout();
}

const std::string &BaseLabel::get_text() const
{
    return (_text);
}

void BaseLabel::set_color(const Color &color)
{
    _color = color;
}

void BaseLabel::set_font_size(unsigned int size)
{
    _update_min_rect = true;
    _size = size;
    if (_app != nullptr)
        _app->update_layout();
}

void BaseLabel::set_text_align(TextAlign align)
{
    _align = align;
    update_align_bitmask();
}

void BaseLabel::set_text_valign(TextVAlign align)
{
    _valign = align;
    update_align_bitmask();
}

void BaseLabel::set_max_length(int length)
{
    _max_length = length;
    set_text(_text);
}

void BaseLabel::apply_font(NVGcontext *ctx)
{
    nvgFontFace(ctx, "montserrat-medium");
    nvgFontSize(ctx, _size);
    nvgTextAlign(ctx, _text_align);
    nvgFillColor(ctx, _color.nvg_color());
}

void BaseLabel::update_align_bitmask()
{
    _text_align = 0;
    switch (_align) {
        default:
        case LEFT:
            _text_align |= NVG_ALIGN_LEFT;
            break;
        case RIGHT:
            _text_align |= NVG_ALIGN_RIGHT;
            break;
        case CENTER:
            _text_align |= NVG_ALIGN_CENTER;
            break;
    }
    switch (_valign) {
        default:
        case TOP:
            _text_align |= NVG_ALIGN_TOP;
            break;
        case BOTTOM:
            _text_align |= NVG_ALIGN_BOTTOM;
            break;
        case MIDDLE:
            _text_align |= NVG_ALIGN_MIDDLE;
            break;
    };
}

}
