
#include "DebugScreen.hpp"
#include "theme/color.hpp"

namespace gana {

DebugScreen::DebugScreen()
{}

DebugScreen::~DebugScreen()
{}

void DebugScreen::draw(NVGcontext *ctx)
{
    nvgBeginPath(ctx);
    nvgRect(ctx, 0, 0, 150, 50);
    nvgFillColor(ctx, theme::DEBUG_BG_COLOR.nvg_color());
    nvgFill(ctx);

    nvgFontFace(ctx, "montserrat-medium");
    nvgFontSize(ctx, 15);
    nvgTextAlign(ctx, NVG_ALIGN_LEFT);
    nvgFillColor(ctx, theme::DEBUG_TEXT_COLOR.nvg_color());

    int y = 20;
    for (auto &val: _values) {
        nvgBeginPath(ctx);
        nvgText(ctx, 0, y, std::string(val.first + ": " + val.second).c_str(), nullptr);
        y += 20;
    }

}

void DebugScreen::set(const std::string &key, const std::string &value)
{
    _values[key] = value;
}

}