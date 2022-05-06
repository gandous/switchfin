
#ifndef LATESTVIEW_HPP_
#define LATESTVIEW_HPP_

#include <string>
#include "gana/ui/ScrollView.hpp"
#include "gana/ui/box_container/HBoxContainer.hpp"
#include "network/JellyfinClient.hpp"

class LatestView: public gana::ScrollView {
    public:
        LatestView(JellyfinClient &client, const std::string &id);
        ~LatestView();

    private:
        void on_latest_receive(gana::Request::RCode code, gana::Request &req);
        JellyfinClient &_jclient;
        std::shared_ptr<ItemListRequest> _rlatest;
        gana::HBoxContainer _ctn_vignette;
};

#endif /* LATESTVIEW_HPP_ */