
#ifndef EPISODE_DETAIL_HPP_
#define EPISODE_DETAIL_HPP_

#include "gana/ui/NavigationManager.hpp"
#include "gana/ui/NetworkImage.hpp"
#include "gana/ui/Label.hpp"
#include "gana/ui/MultiLineLabel.hpp"
#include "gana/ui/GradientColorRect.hpp"
#include "gana/ui/RectContainer.hpp"
#include "gana/ui/TextureButton.hpp"
#include "gana/ui/Button.hpp"
#include "gana/ui/box_container/HBoxContainer.hpp"
#include "gana/ui/box_container/VBoxContainer.hpp"
#include "network/JellyfinClient.hpp"
#include "PlayButtonContainer.hpp"

class EpisodeDetail: public gana::RectContainer {
    public:
        EpisodeDetail(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item);
        ~EpisodeDetail();

    protected:
        void process() override;
    private:
        void on_data_receive(gana::Request::RCode code);
        void on_play_btn_pressed();
        void on_resume_btn_pressed();
        void on_back_btn_pressed();
        gana::NavigationManager &_nav;
        std::shared_ptr<JellyfinClient> _jclient;
        std::shared_ptr<ItemRequest> _rdata;
        const Item &_item;
        gana::NetworkImage _img_background;
        gana::Label _lbl_title;
        gana::Label _lbl_serie_name;
        gana::Label _lbl_episode_number;
        gana::Label _lbl_duration;
        gana::MultiLineLabel _mlbl_overview;
        gana::TextureButton _btn_back;
        gana::GradientColorRect _gdt_background;
        gana::VBoxContainer _ctn_info;
        gana::HBoxContainer _ctn_name_duration;
        gana::VBoxContainer _ctn_split_img_background;
        PlayButtonContainer _ctn_play_button;
};

#endif /* EPISODE_DETAIL_HPP_ */