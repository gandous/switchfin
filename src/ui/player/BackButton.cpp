
#include "gana/ui/box_container/HBoxContainer.hpp"
#include "gana/ui/Image.hpp"
#include "BackButton.hpp"

BackButton::BackButton()
{
    gana::HBoxContainer *ctn = make_managed<gana::HBoxContainer>();
    set_content_margin(4);
    set_color(gana::Color(0, 0, 0, 30));

    gana::Image *img = make_managed<gana::Image>();
    img->set_image("icon/back-48.png");
    ctn->add_child(img);

    _lbl.set_font_size(40);
    _lbl.set_vsizing(gana::Node::Sizing::SHRINK_CENTER);
    _lbl.set_max_length(50);
    ctn->add_child(&_lbl);

    add_child(ctn);
}

BackButton::~BackButton()
{}

void BackButton::set_text(const std::string &text)
{
    _lbl.set_text(text);
}
