
#include "Genre.hpp"

Genre::Genre(const std::string &name)
{
    _lbl_name.set_text(name);
    add_child(&_lbl_name);

    set_content_margin(8);
    set_corner_radius(8);
    set_color(gana::Color(64, 64, 64, 200));
}

Genre::~Genre()
{}
