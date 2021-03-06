
#ifndef HBOXCONTAINER_HPP_
#define HBOXCONTAINER_HPP_

#include "ui/Node.hpp"

namespace gana {

class HBoxContainer: public Node {
    public:
        HBoxContainer();
        ~HBoxContainer();

        void add_child(Node *node) override;
        void update_layout(const Vector2f &size) override;
        Vector2f get_min_size() override;
        void add_spacer(float w = 16, bool expand = false);
        void set_space(float space);
        bool is_focusable() const override;
        virtual void set_top_node(Node *node) override;
        virtual void set_bottom_node(Node *node) override;
    protected:
        void on_focus() override;
    private:
        float _space;
};

}

#endif /* HBOXCONTAINER_HPP_ */