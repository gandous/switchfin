
#include "App.hpp"
#include "Genre.hpp"
#include "SerieDetail.hpp"
#include "MovieDetail.hpp"
#include "ui/home/SmallMovieVignette.hpp"
#include "MediaList.hpp"

static const uint ITEM_PER_ROW = 6;

MediaList::MediaList(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item): _nav(nav), _jclient(client)
{
    set_anchor(gana::Node::Anchor::FULL_RECT);
    set_color(gana::Color(19, 19, 19));

    _rdata = client->get_items(item.get_id());
    _rdata->set_callback(_rdata->mf_callback(*this, &MediaList::on_data_receive));

    gana::ScrollView *vscroll = make_managed<gana::ScrollView>();
    vscroll->set_anchor(gana::Node::FULL_RECT);
    vscroll->set_scroll_direction(gana::ScrollView::Y);
    add_child(vscroll);

    _ctn_main.set_hsizing(gana::Node::Sizing::FILL);
    _ctn_main.set_expand();
    vscroll->add_child(&_ctn_main);

    _btn_back.set_image("icon/back-48.png");
    _btn_back.set_color(gana::Color(0, 0, 0, 70));
    _btn_back.signal_pressed.connect(*this, &MediaList::on_back_btn_pressed);
    _ctn_title.add_child(&_btn_back);

    _lbl_title.set_text(item.get_name());
    _lbl_title.set_font_size(40);
    _lbl_title.set_text_align(gana::BaseLabel::TextAlign::CENTER);
    _lbl_title.set_expand(true);
    _ctn_title.add_child(&_lbl_title);

    _ctn_title.set_hsizing(gana::Node::Sizing::FILL);
    _ctn_main.add_child(&_ctn_title);

    set_process();
}

MediaList::~MediaList()
{}

void MediaList::process()
{
    _jclient->process();
}

void MediaList::on_data_receive(gana::Request::RCode code)
{
    if (code != gana::Request::OK) {
        gana::Logger::error("%s", _rdata->get_error_str().c_str());
        return;
    }
    gana::HBoxContainer *row = create_new_row();
    std::size_t index = 0;
    bool first = true;
    for (auto &item: _rdata->get_items()) {
        SmallMovieVignette *vignette = row->make_managed<SmallMovieVignette>(_jclient->get_http(), _jclient->get_img_url(item.get_id(), JellyfinClient::ImageType::PRIMARY), item);
        vignette->on_click.connect(*this, &MediaList::on_item_click);
        row->add_child(vignette);
        index++;
        if (first) {
            first = false;
            _app->set_focused_node(vignette);
        }
        if (index >= ITEM_PER_ROW) {
            index = 0;
            row = create_new_row();
        }
    }
}

void MediaList::on_back_btn_pressed()
{
    _nav.navigate_up();
}

gana::HBoxContainer *MediaList::create_new_row()
{
    gana::HBoxContainer *ctn = make_managed<gana::HBoxContainer>();
    ctn->set_hsizing(gana::Node::Sizing::SHRINK_CENTER);
    _ctn_main.add_child(ctn);
    return (ctn);
}


void MediaList::on_item_click(const Item &item)
{
    gana::Logger::info("Item click %s", item.get_name().c_str());
    switch (item.get_type()) {
        case Item::MOVIE:
            _nav.navigate_down<MovieDetail>(_jclient, item);
            break;
        case Item::SERIE:
            _nav.navigate_down<SerieDetail>(_jclient, item);
            break;
        default:
            gana::Logger::error("failed to navigate down. Unknow item type");
    }
}
