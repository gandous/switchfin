
#include "gana/ui/Image.hpp"
#include "gana/ui/Label.hpp"
#include "gana/theme/color.hpp"
#include "PlayButtonContainer.hpp"

PlayButtonContainer::PlayButtonContainer()
{
    _btn_play.signal_pressed.connect(*this, &PlayButtonContainer::on_play_btn_pressed);
    _ctn_button.add_child(&_btn_play);

    add_child(&_ctn_button);
}

PlayButtonContainer::~PlayButtonContainer()
{}

void PlayButtonContainer::on_play_btn_pressed()
{
    signal_play_pressed.emit();
}
