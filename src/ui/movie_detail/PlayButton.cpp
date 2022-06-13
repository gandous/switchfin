
#include <sstream>
#include "gana/ui/Image.hpp"
#include "gana/ui/box_container/HBoxContainer.hpp"
#include "gana/theme/color.hpp"
#include "PlayButton.hpp"

PlayButton::PlayButton()
{
    gana::HBoxContainer *ctn_button = make_managed<gana::HBoxContainer>();
    gana::Image *img = ctn_button->make_managed<gana::Image>();
    img->set_image("icon/play-24.png");
    ctn_button->add_child(img);
    _lbl.set_vsizing(gana::Node::Sizing::SHRINK_CENTER);
    _lbl.set_text("Watch");
    ctn_button->add_child(&_lbl);
    add_child(ctn_button);
    set_color(gana::theme::PRIMARY);
    set_content_margin(8);
}

PlayButton::~PlayButton()
{}

void PlayButton::set_label(int season, int episode)
{
    std::ostringstream str;

    str << "S" << season << ":E" << episode;
    _lbl.set_text(str.str());
    _lbl.set_text_align(gana::BaseLabel::CENTER);
}
