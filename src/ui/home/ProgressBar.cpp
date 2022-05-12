
#include "ProgressBar.hpp"

ProgressBar::ProgressBar(): _percentage(0)
{}

ProgressBar::~ProgressBar()
{}

void ProgressBar::draw(NVGcontext *ctx)
{
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, get_draw_positon().x, get_draw_positon().y, get_draw_size().x, get_draw_size().y, 5);
    nvgFillColor(ctx, gana::Color(32, 32, 32, 225).nvg_color());
    nvgFill(ctx);
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, get_draw_positon().x, get_draw_positon().y, get_draw_size().x * _percentage, get_draw_size().y, 5);
    nvgFillColor(ctx, _color.nvg_color());
    nvgFill(ctx);
}

void ProgressBar::set_progress(float percentage)
{
    _percentage = percentage / 100;
}

void ProgressBar::set_color(const gana::Color &color)
{
    _color = color;
}
