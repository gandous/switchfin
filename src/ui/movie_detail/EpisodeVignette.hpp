
#ifndef EPISODEVIGNETTE_HPP_
#define EPISODEVIGNETTE_HPP_

#include "gana/ui/NetworkImage.hpp"
#include "gana/ui/Label.hpp"
#include "gana/ui/MultiLineLabel.hpp"
#include "gana/ui/box_container/VBoxContainer.hpp"
#include "gana/ui/BGRectContainer.hpp"
#include "gana/ui/BaseButton.hpp"
#include "gana/type/Signal.hpp"
#include "network/item/Item.hpp"
#include "network/JellyfinClient.hpp"
#include "PlayButtonContainer.hpp"

class EpisodeVignette: public gana::BaseButton {
    public:
        EpisodeVignette(JellyfinClient &client, const Item &item);
        ~EpisodeVignette();

        gana::Signal<const Item&> signal_item_click;
    private:
        void on_item_click();
        const Item &_item;
        gana::HBoxContainer _ctn;
        gana::VBoxContainer _ctn_text;
        gana::NetworkImage _img;
        gana::Label _lbl_title;
        gana::Label _lbl_duration;
        gana::MultiLineLabel _lbl_overview;
        PlayButtonContainer _ctn_play_button;
};

#endif /* EPISODEVIGNETTE_HPP_ */