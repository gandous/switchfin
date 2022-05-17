
#include "SeasonDetail.hpp"

static const gana::Vector2f SIZE = gana::Vector2f(1280, 720);


SeasonDetail::SeasonDetail(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item): _nav(nav), _jclient(client), _item(item)
{
    set_anchor(gana::Node::Anchor::FULL_RECT);

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

    _lbl_title.set_text(item.get_serie_name());
    _lbl_title.set_font_size(60);
    _lbl_title.set_max_length(30);
    _ctn_episode.add_child(&_lbl_title);

    _lbl_season_nb.set_text(item.get_name());
    _lbl_season_nb.set_font_size(24);
    _lbl_season_nb.set_max_length(30);
    _ctn_episode.add_child(&_lbl_season_nb);

    _ctn_episode.set_margin(16);
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