
#include "App.hpp"
#include "MultiLineLabel.hpp"

namespace gana {

MultiLineLabel::MultiLineLabel()
{}

MultiLineLabel::~MultiLineLabel()
{}

void MultiLineLabel::update_layout(const Vector2f &size)
{
    if (_app != nullptr) {
        float bound[4];

        nvgTextBoxBounds(_app->get_nvg_context(), 0, 0, size.x, _display_text.c_str(), NULL, bound);
        BaseLabel::update_layout(Vector2f(bound[2], bound[3]));
    } else {
        BaseLabel::update_layout(size);
    }
}

void MultiLineLabel::draw_text(NVGcontext *ctx, float x, float y)
{
    nvgTextBox(ctx, x, y, get_draw_size().x, _display_text.c_str(), NULL);
}

void MultiLineLabel::get_bounds(float *box)
{
    box[0] = 0;
    box[1] = 0;
    box[2] = 50;
    box[3] = 20;
}

}
