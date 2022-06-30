
#include "network/item/duration.hpp"
#include "BackButton.hpp"
#include "Player.hpp"

static const float MIN_TIME_WIDTH = 100;
static const float HIDE_UI_TIMER = 3;

Player::Player(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item): _nav(nav)
{
    _player.set_source(client->get_stream_url(item.get_id()));
    _player.signal_file_loaded.connect(*this, &Player::on_file_loaded);
    add_child(&_player);

    BackButton *btn_go_back = _ctn.make_managed<BackButton>();
    btn_go_back->set_text(item.get_name());
    btn_go_back->signal_pressed.connect(*this, &Player::on_go_back_pressed);
    _ctn.add_child(btn_go_back);

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
    _ctn.add_child(&_ctn_duration_bar);

    gana::HBoxContainer *ctn_player_control = make_managed<gana::HBoxContainer>();

    _btn_prev_episode.set_image("icon/prev_episode-48.png");
    ctn_player_control->add_child(&_btn_prev_episode);

    _btn_fast_backward.set_image("icon/fast_backward-48.png");
    ctn_player_control->add_child(&_btn_fast_backward);

    _btn_pause.set_image("icon/pause-48.png");
    _btn_pause.signal_pressed.connect(*this, &Player::on_pause_btn_pressed);
    ctn_player_control->add_child(&_btn_pause);

    _btn_fast_forward.set_image("icon/fast_forward-48.png");
    ctn_player_control->add_child(&_btn_fast_forward);

    _btn_next_episode.set_image("icon/next_episode-48.png");
    ctn_player_control->add_child(&_btn_next_episode);

    ctn_player_control->set_hsizing(gana::Node::Sizing::SHRINK_CENTER);
    _ctn.add_child(ctn_player_control);

    _ctn.set_anchor(gana::Node::Anchor::FULL_RECT);
    _ctn.set_margin(16, 16, 16, 0);
    _ctn_background.add_child(&_ctn);

    _ctn_background.set_anchor(gana::Node::Anchor::FULL_RECT);
    _ctn_background.set_corner_radius(0);
    _ctn_background.set_color(gana::Color(0, 0, 0, 128));
    add_child(&_ctn_background);

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
    if (_ctn_background.is_visible() && evt.type == sf::Event::TouchBegan) {
        _ctn_background.hide();
        evt.handle = true;
    } else if (evt.type != sf::Event::TouchMoved && evt.type != sf::Event::TouchEnded && !evt.cancel_pressed()) {
        _ctn_background.show();
        _timer_hide_ui.start();
        evt.handle = true;
    }
}

void Player::enter_tree()
{
    _app->set_focused_node(&_btn_pause);
}

void Player::process()
{
    if (!_playback_started)
        return;
    if (_slider_bar.has_focus())
        _timer_hide_ui.restart();
    uint64_t time = _slider_bar.has_focus() ? _slider_bar.get_value() : _player.get_time_pos();
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
    for (int i = 0; i < _player.get_track_count(); i++) {
        gana::MPVPlayer::Track track = _player.get_track(i);
        gana::Logger::info("%s %s %ld %d %d", track.title.c_str(), track.lang.c_str(), track.id, track.type, (int)track.selected);
    }
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
    _ctn_background.hide();
}

void Player::on_go_back_pressed()
{
    _nav.navigate_up();
}
