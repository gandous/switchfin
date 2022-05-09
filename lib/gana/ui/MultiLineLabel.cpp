
#include "App.hpp"
#include "MultiLineLabel.hpp"

namespace gana {

MultiLineLabel::MultiLineLabel()
{}

MultiLineLabel::~MultiLineLabel()
{}

void MultiLineLabel::draw_text(NVGcontext *ctx, float x, float y)
{
    nvgTextBox(ctx, x, y, get_draw_size().x, _text.c_str(), NULL);
}

void MultiLineLabel::get_bounds(float *box)
{
    nvgTextBoxBounds(_app->get_nvg_context(), 0, 0, get_draw_size().x, _text.c_str(), NULL, box);
}

}
