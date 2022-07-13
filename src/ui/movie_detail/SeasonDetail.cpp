
#include "gana/ui/box_container/HBoxContainer.hpp"
#include "EpisodeVignette.hpp"
#include "App.hpp"
#include "ui/player/Player.hpp"
#include "SeasonDetail.hpp"

static const gana::Vector2f SIZE = gana::Vector2f(1280, 720);
static const int CTN_MARGIN = 16;

SeasonDetail::SeasonDetail(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item): _nav(nav), _jclient(client), _item(item)
{
    set_anchor(gana::Node::Anchor::FULL_RECT);

    _repisodes = client->get_episodes(item.get_serie_id(), item.get_id());
    _repisodes->set_callback(gana::Request::mf_callback(*this, &SeasonDetail::on_episodes_receive));

    _img_background.set_image(client->get_http(), client->get_img_url(item.get_parent_backdrop_item_id(), JellyfinClient::BACKDROP), {
        {"fillWidth", std::to_string((int)SIZE.x)},
        {"fillHeight", std::to_string((int)SIZE.y)},
        {"quality", "90"},
    });
    add_child(&_img_background);

    _gdt_background.set_icolor(gana::Color(0, 0, 0, 153));
    _gdt_background.set_ocolor(gana::Color(0, 0, 0));
    _gdt_background.set_anchor(gana::Node::FULL_RECT);
    add_child(&_gdt_background);

    gana::HBoxContainer *ctn = make_managed<gana::HBoxContainer>();
    _btn_back.set_image("icon/back-48.png");
    _btn_back.set_color(gana::Color(0, 0, 0, 70));
    _btn_back.signal_pressed.connect(*this, &SeasonDetail::on_back_btn_pressed);
    ctn->add_child(&_btn_back);

    ctn->set_space(16);
    _lbl_title.set_text(item.get_serie_name());
    _lbl_title.set_font_size(60);
    _lbl_title.set_max_length(30);
    ctn->add_child(&_lbl_title);
    _ctn_episode.add_child(ctn);

    _lbl_season_nb.set_text(item.get_name());
    _lbl_season_nb.set_font_size(24);
    _lbl_season_nb.set_max_length(30);
    _ctn_episode.add_child(&_lbl_season_nb);

    _ctn_episode.set_margin(CTN_MARGIN);
    _ctn_episode.set_space(8);
    _ctn_episode.set_min_size(gana::Vector2f(SIZE.x - CTN_MARGIN * 2, SIZE.y));
    _scr_episode.add_child(&_ctn_episode);

    _scr_episode.set_anchor(gana::Node::Anchor::FULL_RECT);
    _scr_episode.set_scroll_direction(gana::ScrollView::ScrollDirection::Y);
    add_child(&_scr_episode);

    set_process(true);
}

SeasonDetail::~SeasonDetail()
{}

void SeasonDetail::process()
{
    _jclient->process();
}

void SeasonDetail::on_episodes_receive(gana::Request::RCode code)
{
    if (code != gana::Request::OK) {
        return;
    }
    for (auto &c: _repisodes->get_items()) {
        EpisodeVignette *vignette = _ctn_episode.make_managed<EpisodeVignette>(*_jclient.get(), c);
        vignette->set_hsizing(gana::Node::Sizing::FILL);
        vignette->signal_item_click.connect(*this, &SeasonDetail::on_item_click);
        _ctn_episode.add_child(vignette);
    }
    _app->set_focused_node(&_ctn_episode);
}

void SeasonDetail::on_back_btn_pressed()
{
    _nav.navigate_up();
}

void SeasonDetail::on_item_click(const Item &item)
{
    _nav.navigate_down<Player>(_jclient, item);
}
