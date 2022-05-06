
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
        virtual void set_left_node(Node *node) override;
        virtual void set_top_node(Node *node) override;
        virtual void set_right_node(Node *node) override;
        virtual void set_bottom_node(Node *node) override;
    protected:
        void enter_tree();
        void on_focus();
    private:
        void on_node_focus(Node *node);
        ScrollDirection _direction;
};

}

#endif /* SCROLLVIEW_HPP_ */