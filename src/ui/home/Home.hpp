
#ifndef HOME_HPP_
#define HOME_HPP_

#include <memory>
#include "ui/box_container/HBoxContainer.hpp"
#include "ui/box_container/VBoxContainer.hpp"
#include "network/JellyfinClient.hpp"
#include "ui/Label.hpp"
#include "ui/ColorRect.hpp"
#include "BigMovieVignette.hpp"

class Home: public gana::ColorRect {
    public:
        Home(std::shared_ptr<JellyfinClient> client);
        ~Home();

    protected:
        void enter_tree() override;
        void process() override;
    private:
        void on_resume_receive(gana::Request::RCode code, gana::Request &req);
        std::shared_ptr<JellyfinClient> _jclient;
        std::shared_ptr<ItemsRequest> _rresume;
        gana::VBoxContainer _ctn_main;
        gana::HBoxContainer _ctn_resume_movie;
        gana::Label _lbl_continue_watching;
};

#endif /* HOME_HPP_ */