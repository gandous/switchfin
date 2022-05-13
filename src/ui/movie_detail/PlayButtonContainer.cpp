
#include "gana/ui/Image.hpp"
#include "gana/ui/Label.hpp"
#include "gana/theme/color.hpp"
#include "PlayButtonContainer.hpp"

PlayButtonContainer::PlayButtonContainer()
{
    gana::HBoxContainer *ctn_button = _btn_play.make_managed<gana::HBoxContainer>();
    gana::Image *img = ctn_button->make_managed<gana::Image>();
    img->set_image("icon/play-24.png");
    ctn_button->add_child(img);
    gana::Label *lbl = ctn_button->make_managed<gana::Label>();
    lbl->set_vsizing(gana::Node::Sizing::SHRINK_CENTER);
    lbl->set_text("Watch");
    ctn_button->add_child(lbl);
    _btn_play.add_child(ctn_button);
    _btn_play.set_color(gana::theme::PRIMARY);
    _btn_play.signal_pressed.connect(*this, &PlayButtonContainer::on_play_btn_pressed);
    _btn_play.set_content_margin(8);
    add_child(&_btn_play);
}

PlayButtonContainer::~PlayButtonContainer()
{}

void PlayButtonContainer::on_play_btn_pressed()
{
    signal_play_pressed.emit();
}
