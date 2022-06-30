
#ifndef BACKBUTTON_HPP_
#define BACKBUTTON_HPP_

#include "gana/ui/BaseButton.hpp"
#include "gana/ui/Label.hpp"

class BackButton: public gana::BaseButton {
    public:
        BackButton();
        ~BackButton();

        void set_text(const std::string &text);
    private:
        gana::Label _lbl;
};

#endif /* BACKBUTTON_HPP_ */