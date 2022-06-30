
#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <memory>
#include "gana/ui/Node.hpp"
#include "gana/ui/NavigationManager.hpp"
#include "gana/ui/MPVPlayer.hpp"
#include "gana/ui/Label.hpp"
#include "gana/ui/box_container/VBoxContainer.hpp"
#include "gana/ui/box_container/HBoxContainer.hpp"
#include "gana/ui/BGRectContainer.hpp"
#include "gana/ui/TextureButton.hpp"
#include "gana/ui/Timer.hpp"
#include "network/JellyfinClient.hpp"
#include "Slider.hpp"

class Player: public gana::Node {
    public:
        Player(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item);
        ~Player();

        void process_event(gana::Event &evt) override;
    protected:
        void process();
    private:
        void on_file_loaded();
        void on_slider_value_changed(uint value);
        void on_pause_btn_pressed();
        void on_hide_timer_timeout();
        gana::MPVPlayer _player;
        gana::VBoxContainer _ctn;
        gana::HBoxContainer _ctn_duration_bar;
        gana::BGRectContainer _ctn_background;
        gana::Label _lbl_current_time;
        gana::Label _lbl_duration;
        gana::TextureButton _btn_pause;
        gana::Timer _timer_hide_ui;
        Slider _slider_bar;
        bool _playback_started = false;
};

#endif /* PLAYER_HPP_ */