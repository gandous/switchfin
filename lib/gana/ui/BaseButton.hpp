
#ifndef BASEBUTTON_HPP_
#define BASEBUTTON_HPP_

#include "ui/BGRectContainer.hpp"
#include "type/Signal.hpp"

namespace gana {

class BaseButton: public BGRectContainer {
    public:
        BaseButton();
        ~BaseButton();

        Signal<> signal_pressed;

        void process_event(Event &evt) override;
    private:
};

}

#endif /* BASEBUTTON_HPP_ */