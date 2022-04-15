
#ifndef LINEEDIT_HPP_
#define LINEEDIT_HPP_

#include <string>
#include "ui/Label.hpp"
#include "type/Color.hpp"

namespace gana {

class LineEdit: public Label {
    public:
        LineEdit();
        ~LineEdit();

        void draw(NVGcontext *ctx) override;
        void process_event(Event &evt) override;
        const std::string &get_value() const;
        void set_value(const std::string &value);
    private:
        void set_text(const std::string &text);
        Color _color;
        std::string _value;
};

}

#endif /* LINEEDIT_HPP_ */