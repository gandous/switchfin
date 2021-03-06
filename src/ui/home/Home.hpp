
#ifndef HOME_HPP_
#define HOME_HPP_

#include <memory>
#include "ui/box_container/HBoxContainer.hpp"
#include "ui/ScrollView.hpp"
#include "ui/box_container/VBoxContainer.hpp"
#include "network/JellyfinClient.hpp"
#include "ui/Label.hpp"
#include "ui/ColorRect.hpp"
#include "ui/NavigationManager.hpp"

class Home: public gana::ColorRect {
    public:
        Home(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client);
        ~Home();

    protected:
        void enter_tree() override;
        void process() override;
    private:
        void on_resume_receive(gana::Request::RCode code);
        void on_next_up_receive(gana::Request::RCode code);
        void on_views_receive(gana::Request::RCode code);
        void on_item_click(const Item &item);
        gana::NavigationManager &_nav;
        std::shared_ptr<JellyfinClient> _jclient;
        std::shared_ptr<ItemsRequest> _rresume;
        std::shared_ptr<ItemsRequest> _rnext_up;
        std::shared_ptr<ItemsRequest> _rviews;
        gana::VBoxContainer _ctn_main;
        gana::HBoxContainer _ctn_resume_movie;
        gana::HBoxContainer _ctn_next_up;
        gana::HBoxContainer _ctn_my_media;
        gana::Label _lbl_continue_watching;
        gana::Label _lbl_next_up;
        gana::Label _lbl_my_media;
        gana::ScrollView _scr_resume;
};

#endif /* HOME_HPP_ */