
#ifndef PLAYBUTTONCONTAINER_HPP_
#define PLAYBUTTONCONTAINER_HPP_

#include "type/Signal.hpp"
#include "gana/ui/BaseButton.hpp"
#include "gana/ui/box_container/HBoxContainer.hpp"

class PlayButtonContainer: public gana::HBoxContainer {
    public:
        PlayButtonContainer();
        ~PlayButtonContainer();

        gana::Signal<> signal_play_pressed;
    private:
        void on_play_btn_pressed();
        gana::BaseButton _btn_play;
};

#endif /* PLAYBUTTONCONTAINER_HPP_ */