
#ifndef SLIDER_HPP_
#define SLIDER_HPP_

#include "gana/ui/Node.hpp"
#include "gana/type/Signal.hpp"

class Slider: public gana::Node {
    public:
        Slider();
        ~Slider();

        gana::Signal<uint> signal_value_changed;

        void draw(NVGcontext *ctx) override;
        void process_event(gana::Event &evt) override;
        void set_max_value(uint value);
        void set_value(uint value);
    private:
        void update_percentage();
        uint _value;
        uint _max_value;
        float _percentage;
        gana::Vector2f _center_sliding_point;
};

#endif /* SLIDER_HPP_ */