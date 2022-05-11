
#include "DebugScreen.hpp"
#include "theme/color.hpp"

static const int SPACING = 4;

namespace gana {

DebugScreen::DebugScreen(): _y_space(0)
{}

DebugScreen::~DebugScreen()
{}

void DebugScreen::draw(NVGcontext *ctx)
{
    nvgFontFace(ctx, "montserrat-medium");
    nvgFontSize(ctx, 15);
    Vector2f bg_size = get_bg_size(ctx);
    nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
    nvgBeginPath(ctx);
    nvgRect(ctx, 0, 0, bg_size.x, bg_size.y);
    nvgFillColor(ctx, theme::DEBUG_BG_COLOR.nvg_color());
    nvgFill(ctx);

    nvgFillColor(ctx, theme::DEBUG_TEXT_COLOR.nvg_color());

    int y = _y_space / 2;
    for (auto &val: _values) {
        nvgBeginPath(ctx);
        nvgText(ctx, 0, y, std::string(val.first + ": " + val.second).c_str(), nullptr);
        y += _y_space;
    }

}

void DebugScreen::set(const std::string &key, const std::string &value)
{
    _values[key] = value;
}

Vector2f DebugScreen::get_bg_size(NVGcontext *ctx)
{
    Vector2f size;
    float bounds[4];

    nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
    for (auto &val: _values) {
        nvgTextBounds(ctx, 0, 0, std::string(val.first + ": " + val.second).c_str(), nullptr, bounds);
        size.x = std::max(size.x, bounds[2]);
        _y_space = bounds[3] + SPACING;
    }
    size.y = _y_space * _values.size();
    return (size);
}

}