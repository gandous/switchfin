
#ifndef SEASONDETAIL_HPP_
#define SEASONDETAIL_HPP_

#include "gana/ui/NavigationManager.hpp"
#include "gana/ui/NetworkImage.hpp"
#include "gana/ui/Label.hpp"
#include "gana/ui/MultiLineLabel.hpp"
#include "gana/ui/GradientColorRect.hpp"
#include "gana/ui/TextureButton.hpp"
#include "gana/ui/RectContainer.hpp"
#include "gana/ui/box_container/VBoxContainer.hpp"
#include "gana/ui/ScrollView.hpp"
#include "PlayButtonContainer.hpp"
#include "network/JellyfinClient.hpp"

class SeasonDetail: public gana::RectContainer {
    public:
        SeasonDetail(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item);
        ~SeasonDetail();

    protected:
        void process() override;
    private:
        void on_episodes_receive(gana::Request::RCode code);
        void on_back_btn_pressed();
        void on_item_click(const Item &item);
        std::shared_ptr<ItemsRequest> _repisodes;
        gana::NavigationManager &_nav;
        std::shared_ptr<JellyfinClient> _jclient;
        const Item &_item;
        gana::NetworkImage _img_background;
        gana::Label _lbl_title;
        gana::Label _lbl_season_nb;
         gana::TextureButton _btn_back;
       gana::GradientColorRect _gdt_background;
        gana::VBoxContainer _ctn_episode;
        gana::ScrollView _scr_episode;
};

#endif /* SEASONDETAIL_HPP_ */