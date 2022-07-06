
#ifndef SERIE_DETAIL_HPP_
#define SERIE_DETAIL_HPP_

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
#include "gana/ui/ScrollView.hpp"
#include "PlayButton.hpp"
#include "network/JellyfinClient.hpp"

class SerieDetail: public gana::RectContainer {
    public:
        SerieDetail(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item);
        ~SerieDetail();

    protected:
        void process() override;
    private:
        void on_data_receive(gana::Request::RCode code);
        void on_seasons_receive(gana::Request::RCode code);
        void on_nextup_receive(gana::Request::RCode code);
        void on_play_btn_pressed();
        void on_resume_btn_pressed();
        void on_back_btn_pressed();
        void on_season_click(const Item &item);
        gana::NavigationManager &_nav;
        std::shared_ptr<JellyfinClient> _jclient;
        std::shared_ptr<ItemRequest> _rdata;
        std::shared_ptr<ItemsRequest> _seasonsdata;
        std::shared_ptr<ItemsRequest> _nextupdata;
        const Item &_item;
        gana::NetworkImage _img_background;
        gana::NetworkImage _img_vignette;
        gana::Label _lbl_title;
        gana::MultiLineLabel _mlbl_overview;
        gana::TextureButton _btn_back;
        gana::GradientColorRect _gdt_background;
        gana::HBoxContainer _ctn_info;
        gana::HBoxContainer _ctn_genres;
        gana::VBoxContainer _ctn_overview;
        gana::HBoxContainer _ctn_seasons;
        PlayButton _play_button;
        gana::ScrollView _scr_seasons;
};

#endif /* SERIE_DETAIL_HPP_ */