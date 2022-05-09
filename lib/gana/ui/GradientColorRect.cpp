
#include "App.hpp"
#include "AssetManager.hpp"
#include "GradientColorRect.hpp"

namespace gana {

GradientColorRect::GradientColorRect(): _radius(0)
{}

GradientColorRect::~GradientColorRect()
{}

void GradientColorRect::draw(NVGcontext *ctx)
{
    nvgSave(ctx);
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, get_draw_positon().x, get_draw_positon().y, get_draw_size().x, get_draw_size().y, _radius);
    nvgTranslate(ctx, get_draw_positon().x, get_draw_positon().y);
    nvgFillPaint(ctx, _paint);
    nvgFill(ctx);
    nvgRestore(ctx);
}

void GradientColorRect::set_size(const Vector2f &size)
{
    Node::set_size(size);
    update_gradient();
}

void GradientColorRect::set_icolor(const Color &color)
{
    _icolor = color;
    update_gradient();
}

void GradientColorRect::set_ocolor(const Color &color)
{
    _ocolor = color;
    update_gradient();
}

void GradientColorRect::set_corner_radius(float radius)
{
    _radius = radius;
    update_gradient();
}

void GradientColorRect::enter_tree()
{
    update_gradient();
}

void GradientColorRect::update_gradient()
{
    if (_app == nullptr)
        return;
    _paint = nvgLinearGradient(_app->get_nvg_context(), 0, 0, 0, get_draw_size().y, _icolor.nvg_color(), _ocolor.nvg_color());}

}
