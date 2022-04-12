
#include "Color.hpp"

namespace gana {

Color::Color(): r(0), g(0), b(0), a(255)
{}

Color::Color(int r, int g, int b, int a): r(r), g(g), b(b), a(a)
{}

Color::Color(int r, int g, int b): r(r), g(g), b(b), a(255)
{}

Color::~Color()
{}

NVGcolor Color::nvg_color() const
{
    return (nvgRGBA(r, g, b, a));
}

}
