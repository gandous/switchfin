
#include "network/item/duration.hpp"
#include "Player.hpp"

static const float MIN_TIME_WIDTH = 100;

Player::Player(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item)
{
    _player.set_source(client->get_stream_url(item.get_id()));
    _player.signal_file_loaded.connect(*this, &Player::on_file_loaded);
    add_child(&_player);

    _ctn.add_spacer(8, true);

    _lbl_current_time.set_text("-");
    _lbl_current_time.set_min_size(gana::Vector2f(MIN_TIME_WIDTH, 0));
    _lbl_current_time.set_text_align(gana::BaseLabel::TextAlign::CENTER);
    _ctn_duration_bar.add_child(&_lbl_current_time);

    _slider_bar.signal_value_changed.connect(*this, &Player::on_slider_value_changed);
    _slider_bar.set_expand();
    _ctn_duration_bar.add_child(&_slider_bar);

    _lbl_duration.set_text("-");
    _lbl_duration.set_min_size(gana::Vector2f(MIN_TIME_WIDTH, 0));
    _lbl_duration.set_text_align(gana::BaseLabel::TextAlign::CENTER);
    _ctn_duration_bar.add_child(&_lbl_duration);

    _ctn_duration_bar.set_hsizing(gana::Node::Sizing::FILL);
    _ctn_duration_bar.set_margin(16, 0, 16, 0);
    _ctn.add_child(&_ctn_duration_bar);

    _ctn.set_anchor(gana::Node::Anchor::FULL_RECT);
    add_child(&_ctn);

    set_anchor(gana::Node::Anchor::FULL_RECT);
}

Player::~Player()
{}

void Player::process()
{
    uint64_t time = _player.get_time_pos();
    _slider_bar.set_value(time);
    _lbl_current_time.set_text(mpv_tick_to_duration(time));
}

void Player::on_file_loaded()
{
    set_process();
    uint64_t time = _player.get_time_pos();
    _slider_bar.set_max_value(_player.get_duration());
    _slider_bar.set_value(time);
    _lbl_current_time.set_text(mpv_tick_to_duration(time));
   _lbl_duration.set_text(mpv_tick_to_duration(_player.get_duration()));
}

void Player::on_slider_value_changed(uint value)
{
    _player.set_time_pos(value);
}