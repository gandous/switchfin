
#include "Label.hpp"
#include "App.hpp"

namespace gana {

Label::Label(): _size(20), _update_min_rect(true)
{}

Label::~Label()
{}

void Label::draw(NVGcontext *ctx)
{
    nvgBeginPath(ctx);
    apply_font(ctx);
    nvgText(ctx, get_position().x, get_position().y + get_size().y / 2, _text.c_str(), NULL);
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
}

void Label::set_color(const Color &color)
{
    _color = color;
}

void Label::set_font_size(unsigned int size)
{
    _update_min_rect = true;
    _size = size;
}

void Label::apply_font(NVGcontext *ctx)
{
    nvgFontFace(ctx, "montserrat-medium");
    nvgFontSize(ctx, _size);
    nvgTextAlign(ctx, NVG_ALIGN_MIDDLE);
    nvgFillColor(ctx, _color.nvg_color());
}

}
