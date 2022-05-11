
#include "SmallMovieVignette.hpp"
#include "LatestView.hpp"

LatestView::LatestView(JellyfinClient &client, const std::string &id): _jclient(client)
{
    set_hsizing(gana::Node::Sizing::FILL);
    set_scroll_direction(gana::ScrollView::X);
    add_child(&_ctn_vignette);

    _rlatest = client.get_latest(id);
    _rlatest->set_callback(gana::Request::mf_callback(*this, &LatestView::on_latest_receive));
}

LatestView::~LatestView()
{}

void LatestView::on_latest_receive(gana::Request::RCode code, gana::Request &req)
{
    if (code != gana::Request::OK) {
        gana::Logger::error("%s", _rlatest->get_error_str().c_str());
        return;
    }
    for (auto &item: _rlatest->get_items()) {
        SmallMovieVignette *vign = _ctn_vignette.make_managed<SmallMovieVignette>(_jclient.get_http(), _jclient.get_img_url(item.get_id(), JellyfinClient::PRIMARY), item);
        vign->set_vsizing(gana::Node::Sizing::SHRINK_CENTER);
        vign->on_click.connect(*this, &LatestView::on_subitem_click);
        gana::Logger::info("Movie: %s", item.get_name().c_str());
        _ctn_vignette.add_child(vign);
    }
}

void LatestView::on_subitem_click(const Item &item)
{
    on_item_selected.emit(item);
}
