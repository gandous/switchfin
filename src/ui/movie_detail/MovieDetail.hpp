
#ifndef MOVIE_DETAIL_HPP_
#define MOVIE_DETAIL_HPP_

#include "gana/ui/NavigationManager.hpp"
#include "gana/ui/NetworkImage.hpp"
#include "gana/ui/Label.hpp"
#include "gana/ui/MultiLineLabel.hpp"
#include "gana/ui/GradientColorRect.hpp"
#include "gana/ui/RectContainer.hpp"
#include "gana/ui/Button.hpp"
#include "gana/ui/box_container/HBoxContainer.hpp"
#include "gana/ui/box_container/VBoxContainer.hpp"
#include "network/JellyfinClient.hpp"

class MovieDetail: public gana::RectContainer {
    public:
        MovieDetail(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item);
        ~MovieDetail();

    protected:
        void process() override;
    private:
        void on_data_receive(gana::Request::RCode code, gana::Request &req);
        void on_play_btn_pressed();
        void on_resume_btn_pressed();
        gana::NavigationManager &_nav;
        std::shared_ptr<JellyfinClient> _jclient;
        std::shared_ptr<ItemRequest> _rdata;
        const Item &_item;
        gana::NetworkImage _img_background;
        gana::NetworkImage _img_vignette;
        gana::Label _lbl_title;
        gana::MultiLineLabel _mlbl_overview;
        gana::GradientColorRect _gdt_background;
        gana::HBoxContainer _ctn_info;
        gana::HBoxContainer _ctn_play_button;
        gana::VBoxContainer _ctn_split_img_background;
        gana::VBoxContainer _ctn_overview;
        gana::Button _btn_resume;
        gana::Button _btn_play;
};

#endif /* MOVIE_DETAIL_HPP_ */