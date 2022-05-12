
#ifndef PROGRESSBAR_HPP_
#define PROGRESSBAR_HPP_

#include "gana/ui/Node.hpp"
#include "gana/type/Color.hpp"

class ProgressBar: public gana::Node {
    public:
        ProgressBar();
        ~ProgressBar();

        void draw(NVGcontext *ctx) override;
        void set_progress(float percentage);
        void set_color(const gana::Color &color);
    private:
        float _percentage;
        gana::Color _color;
};

#endif /* PROGRESSBAR_HPP_ */