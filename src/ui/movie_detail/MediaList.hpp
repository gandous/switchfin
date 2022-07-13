
#ifndef MEDIA_DETAIL_HPP_
#define MEDIA_DETAIL_HPP_

#include "gana/ui/NavigationManager.hpp"
#include "gana/ui/NetworkImage.hpp"
#include "gana/ui/Label.hpp"
#include "gana/ui/MultiLineLabel.hpp"
#include "gana/ui/GradientColorRect.hpp"
#include "gana/ui/ColorRect.hpp"
#include "gana/ui/TextureButton.hpp"
#include "gana/ui/Button.hpp"
#include "gana/ui/box_container/HBoxContainer.hpp"
#include "gana/ui/box_container/VBoxContainer.hpp"
#include "gana/ui/ScrollView.hpp"
#include "network/JellyfinClient.hpp"

class MediaList: public gana::ColorRect {
    public:
        MediaList(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item);
        ~MediaList();

    protected:
        void process() override;
    private:
        void on_data_receive(gana::Request::RCode code);
        void on_back_btn_pressed();
        void on_item_click(const Item &item);
        gana::HBoxContainer *create_new_row();
        gana::NavigationManager &_nav;
        std::shared_ptr<ItemsRequest> _rdata;
        std::shared_ptr<JellyfinClient> _jclient;
        gana::VBoxContainer _ctn_main;
        gana::HBoxContainer _ctn_title;
        gana::Label _lbl_title;
        gana::TextureButton _btn_back;
};

#endif /* MEDIA_DETAIL_HPP_ */