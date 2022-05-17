
#include "App.hpp"
#include "ui/player/Player.hpp"
#include "Genre.hpp"
#include "SeasonVignette.hpp"
#include "SeasonDetail.hpp"
#include "SerieDetail.hpp"

static const gana::Vector2f SIZE = gana::Vector2f(1280, 720);
static const gana::Vector2f VIGNETTE_SIZE = gana::Vector2f(284, 425);
static const int OVERVIEW_MIN_H = 125;

SerieDetail::SerieDetail(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item): _nav(nav), _jclient(client), _item(item)
{
    set_anchor(gana::Node::Anchor::FULL_RECT);

    _rdata = client->get_info(item.get_id());
    _rdata->set_callback(_rdata->mf_callback(*this, &SerieDetail::on_data_receive));
    _seasonsdata = client->get_seasons(item.get_id());
    _seasonsdata->set_callback(_seasonsdata->mf_callback(*this, &SerieDetail::on_seasons_receive));

    _img_background.set_image(client->get_http(), client->get_img_url(item.get_id(), item.get_type() == Item::EPISODE ? JellyfinClient::PRIMARY : JellyfinClient::BACKDROP), {
        {"fillWidth", std::to_string((int)SIZE.x)},
        {"fillHeight", std::to_string((int)SIZE.y)},
        {"quality", "90"},
    });
    add_child(&_img_background);

    _gdt_background.set_icolor(gana::Color(0, 0, 0, 153));
    _gdt_background.set_ocolor(gana::Color(0, 0, 0));
    _gdt_background.set_anchor(gana::Node::FULL_RECT);
    add_child(&_gdt_background);

    _img_vignette.set_image(client->get_http(), client->get_img_url(item.get_id(), item.get_type() == Item::EPISODE ? JellyfinClient::BACKDROP : JellyfinClient::PRIMARY), {
        {"fillWidth", std::to_string((int)VIGNETTE_SIZE.x)},
        {"fillHeight", std::to_string((int)VIGNETTE_SIZE.y)},
        {"quality", "90"},
    });
    _img_vignette.set_corner_radius(8);
    _img_vignette.set_min_size(VIGNETTE_SIZE);
    _img_vignette.set_vsizing(gana::Node::Sizing::SHRINK_CENTER);
    _ctn_info.add_child(&_img_vignette);

    _lbl_title.set_text(item.get_name());
    _lbl_title.set_font_size(60);
    _lbl_title.set_max_length(30);
    _ctn_overview.add_child(&_lbl_title);

    _ctn_genres.set_space(8);
    _ctn_overview.add_child(&_ctn_genres);

    _mlbl_overview.set_hsizing(gana::Node::Sizing::FILL);
    _mlbl_overview.set_min_size(gana::Vector2f(50, OVERVIEW_MIN_H));
    _ctn_overview.add_child(&_mlbl_overview);

    _ctn_play_button.signal_play_pressed.connect(*this, &SerieDetail::on_play_btn_pressed);
    _ctn_overview.add_child(&_ctn_play_button);

    _scr_seasons.add_child(&_ctn_seasons);

    _scr_seasons.set_hsizing(gana::Node::Sizing::FILL);
    _scr_seasons.set_scroll_direction(gana::ScrollView::ScrollDirection::X);
    _ctn_overview.add_child(&_scr_seasons);

    _ctn_overview.set_margin(0, 32, 0, 0);
    _ctn_overview.set_expand();
    _ctn_overview.set_space(12);
    _ctn_info.add_child(&_ctn_overview);

    _ctn_info.set_space(32);
    _ctn_info.set_margin(32);
    _ctn_info.set_hsizing(gana::Node::Sizing::FILL);
    add_child(&_ctn_info);

    set_process();
}

SerieDetail::~SerieDetail()
{}

void SerieDetail::process()
{
    _jclient->process();
}

void SerieDetail::on_data_receive(gana::Request::RCode code, gana::Request &req)
{
    if (code != gana::Request::OK) {
        return;
    }
    const Item &item = _rdata->get_item();
    for (auto &c: item.get_genres()) {
        Genre *genre = _ctn_genres.make_managed<Genre>(c);
        _ctn_genres.add_child(genre);
    }
    _mlbl_overview.set_text(item.get_overview());
    _app->set_focused_node(&_ctn_play_button);
}

void SerieDetail::on_seasons_receive(gana::Request::RCode code, gana::Request &req)
{
    if (code != gana::Request::OK) {
        return;
    }
    for (auto &item: _seasonsdata->get_items()) {
        SeasonVignette *vign = _ctn_seasons.make_managed<SeasonVignette>(*_jclient.get(), item);
        vign->signal_pressed.connect(*this, &SerieDetail::on_season_click);
        _ctn_seasons.add_child(vign);
    }
}

void SerieDetail::on_play_btn_pressed()
{
    gana::Logger::info("Play");
    _nav.navigate_down<Player>(_jclient, _rdata->get_item());
}

void SerieDetail::on_resume_btn_pressed()
{
    gana::Logger::info("Resume");
}

void SerieDetail::on_season_click(const Item &item)
{
    _nav.navigate_down<SeasonDetail>(_jclient, item);
}
