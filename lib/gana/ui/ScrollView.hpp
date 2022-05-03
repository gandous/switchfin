
#ifndef SCROLLVIEW_HPP_
#define SCROLLVIEW_HPP_

#include "ui/Node.hpp"

namespace gana {

class ScrollView: public gana::Node {
    public:
        ScrollView();
        ~ScrollView();

        enum ScrollDirection {
            X = 1 << 0,
            Y = 1 << 1,
            XY = X | Y,
        };

        void add_child(Node *node) override;
        Vector2f get_min_size() override;
        void draw(NVGcontext *ctx) override;
        void set_scroll_direction(ScrollDirection direction);
    protected:
        void enter_tree();
    private:
        void on_node_focus(Node *node);
        ScrollDirection _direction;
};

}

#endif /* SCROLLVIEW_HPP_ */