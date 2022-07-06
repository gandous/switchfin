
#include <sstream>
#include "App.hpp"
#include "ui/player/Player.hpp"
#include "Genre.hpp"
#include "network/item/duration.hpp"
#include "gana/theme/color.hpp"
#include "MovieDetail.hpp"

static const gana::Vector2f SIZE = gana::Vector2f(1280, 720);
static const gana::Vector2f VIGNETTE_SIZE = gana::Vector2f(224, 336);

MovieDetail::MovieDetail(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item): _nav(nav), _jclient(client), _item(item)
{
    set_anchor(gana::Node::Anchor::FULL_RECT);

    _rdata = client->get_info(item.get_id());
    _rdata->set_callback(_rdata->mf_callback(*this, &MovieDetail::on_data_receive));

    _img_background.set_image(client->get_http(), client->get_img_url(item.get_id(), JellyfinClient::BACKDROP), {
        {"fillWidth", std::to_string((int)SIZE.x)},
        {"fillHeight", std::to_string((int)SIZE.y)},
        {"quality", "90"},
    });
    add_child(&_img_background);

    _gdt_background.set_icolor(gana::Color(0, 0, 0, 0));
    _gdt_background.set_ocolor(gana::Color(0, 0, 0));
    _gdt_background.set_anchor(gana::Node::FULL_RECT);
    add_child(&_gdt_background);

    _img_vignette.set_image(client->get_http(), client->get_img_url(item.get_id(), JellyfinClient::PRIMARY), {
        {"fillWidth", std::to_string((int)VIGNETTE_SIZE.x)},
        {"fillHeight", std::to_string((int)VIGNETTE_SIZE.y)},
        {"quality", "90"},
    });
    _img_vignette.set_corner_radius(8);
    _img_vignette.set_min_size(VIGNETTE_SIZE);
    _ctn_info.add_child(&_img_vignette);

    _lbl_title.set_text(item.get_name());
    _lbl_title.set_font_size(60);
    _lbl_title.set_max_length(30);
    _ctn_overview.add_child(&_lbl_title);

    std::ostringstream str;
    str << tick_to_duration(item.get_runtime_tick()) << " " << item.get_prod_year();
    _lbl_duration.set_text(str.str());
    _lbl_duration.set_color(gana::theme::TEXT_COLOR_SECONDARY);
    _ctn_overview.add_child(&_lbl_duration);

    _ctn_genres.set_space(8);
    _ctn_overview.add_child(&_ctn_genres);

    _mlbl_overview.set_hsizing(gana::Node::Sizing::FILL);
    _ctn_overview.add_child(&_mlbl_overview);

    _ctn_play_button.signal_play_pressed.connect(*this, &MovieDetail::on_play_btn_pressed);
    _ctn_overview.add_child(&_ctn_play_button);

    _ctn_overview.set_margin(0, 24, 0, 0);
    _ctn_overview.set_expand();
    _ctn_overview.set_space(12);
    _ctn_info.add_child(&_ctn_overview);

    _btn_back.set_image("icon/back-48.png");
    _btn_back.set_color(gana::Color(0, 0, 0, 70));
    _btn_back.signal_pressed.connect(*this, &MovieDetail::on_back_btn_pressed);
    _ctn_split_img_background.add_child(&_btn_back);

    _ctn_split_img_background.add_spacer(8, true);
    _ctn_split_img_background.set_margin(32);
    add_child(&_ctn_split_img_background);

    _ctn_info.set_space(32);
    _ctn_info.set_hsizing(gana::Node::Sizing::FILL);
    _ctn_split_img_background.add_child(&_ctn_info);

    set_process();
}

MovieDetail::~MovieDetail()
{}

void MovieDetail::process()
{
    _jclient->process();
}

void MovieDetail::on_data_receive(gana::Request::RCode code)
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

void MovieDetail::on_play_btn_pressed()
{
    gana::Logger::info("Play");
    _nav.navigate_down<Player>(_jclient, _rdata->get_item());
}

void MovieDetail::on_resume_btn_pressed()
{
    gana::Logger::info("Resume");
}

void MovieDetail::on_back_btn_pressed()
{
    _nav.navigate_up();
}
