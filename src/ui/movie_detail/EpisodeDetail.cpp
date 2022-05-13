
#include <sstream>
#include "App.hpp"
#include "ui/player/Player.hpp"
#include "network/item/duration.hpp"
#include "EpisodeDetail.hpp"

static const gana::Vector2f SIZE = gana::Vector2f(1280, 720);
static const gana::Vector2f VIGNETTE_SIZE = gana::Vector2f(400, 200);

EpisodeDetail::EpisodeDetail(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item): _nav(nav), _jclient(client), _item(item)
{
    set_anchor(gana::Node::Anchor::FULL_RECT);

    _rdata = client->get_info(item.get_id());
    _rdata->set_callback(_rdata->mf_callback(*this, &EpisodeDetail::on_data_receive));

    _img_background.set_image(client->get_http(), client->get_img_url(item.get_id(), JellyfinClient::PRIMARY), {
        {"fillWidth", std::to_string((int)SIZE.x)},
        {"fillHeight", std::to_string((int)SIZE.y)},
        {"quality", "90"},
    });
    add_child(&_img_background);

    _gdt_background.set_icolor(gana::Color(0, 0, 0, 0));
    _gdt_background.set_ocolor(gana::Color(0, 0, 0));
    _gdt_background.set_anchor(gana::Node::FULL_RECT);
    add_child(&_gdt_background);

    _lbl_serie_name.set_text(item.get_serie_name());
    _lbl_serie_name.set_preset(gana::Label::Preset::SECONDARY);
    _ctn_name_duration.add_child(&_lbl_serie_name);

    std::ostringstream str;
    str << "S" << item.get_parent_index_number() << ":E" << item.get_index_number();
    _lbl_episode_number.set_text(str.str());
    _lbl_episode_number.set_preset(gana::Label::Preset::SECONDARY);
    _ctn_name_duration.add_child(&_lbl_episode_number);

    _lbl_duration.set_text(tick_to_duration(item.get_runtime_tick()));
    _lbl_duration.set_preset(gana::Label::Preset::SECONDARY);
    _ctn_name_duration.add_child(&_lbl_duration);

    _ctn_name_duration.set_space(8);
    _ctn_info.add_child(&_ctn_name_duration);

    _mlbl_overview.set_hsizing(gana::Node::Sizing::FILL);
    _ctn_info.add_child(&_mlbl_overview);

    _ctn_play_button.signal_play_pressed.connect(*this, &EpisodeDetail::on_play_btn_pressed);
    _ctn_info.add_child(&_ctn_play_button);

    _ctn_split_img_background.add_spacer(8, true);
    _ctn_split_img_background.set_margin(32);
    add_child(&_ctn_split_img_background);

    _lbl_title.set_text(item.get_name());
    _lbl_title.set_font_size(60);
    _lbl_title.set_max_length(40);
    _ctn_split_img_background.add_child(&_lbl_title);

    _ctn_info.set_space(16);
    _ctn_info.set_hsizing(gana::Node::Sizing::FILL);
    _ctn_split_img_background.add_child(&_ctn_info);

    set_process();
}

EpisodeDetail::~EpisodeDetail()
{}

void EpisodeDetail::process()
{
    _jclient->process();
}

void EpisodeDetail::on_data_receive(gana::Request::RCode code, gana::Request &req)
{
    if (code != gana::Request::OK) {
        return;
    }
    const Item &item = _rdata->get_item();
    _mlbl_overview.set_text(item.get_overview());
    _app->set_focused_node(&_ctn_play_button);
}

void EpisodeDetail::on_play_btn_pressed()
{
    gana::Logger::info("Play");
    _nav.navigate_down<Player>(_jclient, _rdata->get_item());
}

void EpisodeDetail::on_resume_btn_pressed()
{
    gana::Logger::info("Resume");
}
