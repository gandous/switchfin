
#include "Label.hpp"
#include "App.hpp"
#include "theme/color.hpp"

namespace gana {

Label::Label():
    _color(theme::TEXT_COLOR_W),
    _size(20),
    _update_min_rect(true),
    _text_align(NVG_ALIGN_MIDDLE | NVG_ALIGN_LEFT),
    _align(LEFT)
{}

Label::~Label()
{}

void Label::draw(NVGcontext *ctx)
{
    float x = get_position().x;

    nvgBeginPath(ctx);
    apply_font(ctx);
    if (_align == TextAlign::CENTER)
        x += get_size().x / 2;
    else if (_align == TextAlign::RIGHT)
        x += get_size().x;
    nvgText(ctx, x, get_position().y + get_size().y / 2, _text.c_str(), NULL);
}

Vector2f Label::get_min_size()
{
    if (_app == nullptr)
        return (Vector2f());
    if (_update_min_rect) {
        apply_font(_app->get_nvg_context());
        float box[4] = {0, 0, 0, 0};
        nvgTextAlign(_app->get_nvg_context(), NVG_ALIGN_TOP);
        nvgTextBounds(_app->get_nvg_context(), 0, 0, _text.c_str(), NULL, box);
        _min_rect.x = std::max(box[2], Node::get_min_size().x);
        _min_rect.y = std::max(box[3], Node::get_min_size().y);
        _update_min_rect = false;
    }
    return (_min_rect);
}

void Label::set_text(const std::string &text)
{
    _text = text;
    _update_min_rect = true;
    if (_app != nullptr)
        _app->update_layout();
}

const std::string &Label::get_text() const
{
    return (_text);
}

void Label::set_color(const Color &color)
{
    _color = color;
}

void Label::set_font_size(unsigned int size)
{
    _update_min_rect = true;
    _size = size;
    if (_app != nullptr)
        _app->update_layout();
}

void Label::set_text_align(TextAlign align)
{
    _align = align;
    switch (align) {
        default:
        case LEFT:
            _text_align = NVG_ALIGN_MIDDLE | NVG_ALIGN_LEFT;
            break;
        case RIGHT:
            _text_align = NVG_ALIGN_MIDDLE | NVG_ALIGN_RIGHT;
            break;
        case CENTER:
            _text_align = NVG_ALIGN_MIDDLE | NVG_ALIGN_CENTER;
            break;
    }
}

void Label::set_preset(Preset preset)
{
    switch (preset) {
        case Preset::ERROR:
            set_color(theme::TEXT_COLOR_ERROR);
        default:
            break;
    }
}

void Label::apply_font(NVGcontext *ctx)
{
    nvgFontFace(ctx, "montserrat-medium");
    nvgFontSize(ctx, _size);
    nvgTextAlign(ctx, _text_align);
    nvgFillColor(ctx, _color.nvg_color());
}

}
