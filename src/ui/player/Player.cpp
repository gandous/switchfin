
#include "network/item/duration.hpp"
#include "Player.hpp"

static const float MIN_TIME_WIDTH = 100;
static const float HIDE_UI_TIMER = 5;

Player::Player(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item)
{
    (void)nav;
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

    gana::HBoxContainer *ctn_player_control = make_managed<gana::HBoxContainer>();

    _btn_pause.set_image("icon/pause-48.png");
    _btn_pause.signal_pressed.connect(*this, &Player::on_pause_btn_pressed);
    ctn_player_control->add_child(&_btn_pause);

    ctn_player_control->set_hsizing(gana::Node::Sizing::SHRINK_CENTER);
    _ctn.add_child(ctn_player_control);

    _ctn.set_anchor(gana::Node::Anchor::FULL_RECT);
    add_child(&_ctn);

    _timer_hide_ui.timeout.connect(*this, &Player::on_hide_timer_timeout);
    add_child(&_timer_hide_ui);
    _timer_hide_ui.start(HIDE_UI_TIMER);

    set_anchor(gana::Node::Anchor::FULL_RECT);
    set_process();
}

Player::~Player()
{}

void Player::process_event(gana::Event &evt)
{
    _ctn.show();
    _timer_hide_ui.start();
}

void Player::process()
{
    if (!_playback_started)
        return;
    uint64_t time = _player.get_time_pos();
    _slider_bar.set_value(time);
    _lbl_current_time.set_text(mpv_tick_to_duration(time));
}

void Player::on_file_loaded()
{
    _playback_started = true;
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

void Player::on_pause_btn_pressed()
{
    bool is_pause = _player.is_pause();
    _player.set_pause(!is_pause);
    _btn_pause.set_image((!is_pause) ? "icon/play-48.png" : "icon/pause-48.png");
}

void Player::on_hide_timer_timeout()
{
    _ctn.hide();
}
