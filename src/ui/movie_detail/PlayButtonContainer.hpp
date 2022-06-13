
#ifndef PLAYBUTTONCONTAINER_HPP_
#define PLAYBUTTONCONTAINER_HPP_

#include "type/Signal.hpp"
#include "PlayButton.hpp"
#include "gana/ui/box_container/HBoxContainer.hpp"

class PlayButtonContainer: public gana::HBoxContainer {
    public:
        PlayButtonContainer();
        ~PlayButtonContainer();

        gana::Signal<> signal_play_pressed;
    private:
        void on_play_btn_pressed();
        gana::HBoxContainer _ctn_button;
        PlayButton _btn_play;
};

#endif /* PLAYBUTTONCONTAINER_HPP_ */