
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
        enum SizeMode {
            // Use biggest child as current size
            BiggestChild,
            // Use size given by parent as size
            LayoutSize,
        };

        void update_layout(const Vector2f &size) override;
        void add_child(Node *node) override;
        bool has_child(const Node *node) override;
        Vector2f get_min_size() override;
        void draw(NVGcontext *ctx) override;
        void set_scroll_direction(ScrollDirection direction);
        bool is_focusable() const;
        void preprocess_event(Event &evt) override;
        virtual void set_left_node(Node *node) override;
        virtual void set_top_node(Node *node) override;
        virtual void set_right_node(Node *node) override;
        virtual void set_bottom_node(Node *node) override;
    protected:
        void enter_tree() override;
        void exit_tree() override;
        void on_focus();
    private:
        void on_node_focus(Node *node);
        bool is_top_selectable(Node *node);
        bool is_bottom_selectable(Node *node);
        ScrollDirection _direction;
};

}

#endif /* SCROLLVIEW_HPP_ */