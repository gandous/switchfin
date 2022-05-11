
#ifndef LATESTVIEW_HPP_
#define LATESTVIEW_HPP_

#include <string>
#include "gana/type/Signal.hpp"
#include "gana/ui/ScrollView.hpp"
#include "gana/ui/box_container/HBoxContainer.hpp"
#include "network/JellyfinClient.hpp"

class LatestView: public gana::ScrollView {
    public:
        LatestView(JellyfinClient &client, const std::string &id);
        ~LatestView();

        gana::Signal<const Item&> on_item_selected;
    private:
        void on_latest_receive(gana::Request::RCode code, gana::Request &req);
        void on_subitem_click(const Item &item);
        JellyfinClient &_jclient;
        std::shared_ptr<ItemListRequest> _rlatest;
        gana::HBoxContainer _ctn_vignette;
};

#endif /* LATESTVIEW_HPP_ */