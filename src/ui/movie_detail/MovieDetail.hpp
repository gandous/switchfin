
#ifndef MOVIE_DETAIL_HPP_
#define MOVIE_DETAIL_HPP_

#include "gana/ui/NavigationManager.hpp"
#include "gana/ui/NetworkImage.hpp"
#include "gana/ui/Label.hpp"
#include "gana/ui/GradientColorRect.hpp"
#include "gana/ui/RectContainer.hpp"
#include "gana/ui/box_container/HBoxContainer.hpp"
#include "gana/ui/box_container/VBoxContainer.hpp"
#include "network/JellyfinClient.hpp"

class MovieDetail: public gana::RectContainer {
    public:
        MovieDetail(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item);
        ~MovieDetail();

    protected:
        void process() override;
        std::shared_ptr<JellyfinClient> _jclient;
    private:
        const Item &_item;
        gana::NetworkImage _img_background;
        gana::NetworkImage _img_vignette;
        gana::Label _lbl_title;
        gana::GradientColorRect _gdt_background;
        gana::HBoxContainer _ctn_info;
        gana::VBoxContainer _ctn_split_img_background;
};

#endif /* MOVIE_DETAIL_HPP_ */