
#ifndef PLAYBUTTON_HPP_
#define PLAYBUTTON_HPP_

#include "gana/ui/Label.hpp"
#include "gana/ui/BaseButton.hpp"

class PlayButton: public gana::BaseButton {
    public:
        PlayButton();
        ~PlayButton();

        void set_label(int season, int episode);
    private:
        gana::Label _lbl;
};

#endif /* PLAYBUTTON_HPP_ */