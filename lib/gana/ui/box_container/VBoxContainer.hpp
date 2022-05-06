
#ifndef VBoxContainer_HPP_
#define VBoxContainer_HPP_

#include "ui/Node.hpp"

namespace gana {

class VBoxContainer: public Node {
    public:
        VBoxContainer();
        ~VBoxContainer();

        void add_child(Node *node) override;
        void update_layout(const Vector2f &size) override;
        Vector2f get_min_size() override;
        void add_spacer(float h = 16, bool expand = false);
        void set_space(float space);
        virtual void set_left_node(Node *node) override;
        virtual void set_right_node(Node *node) override;
    protected:
        void on_focus() override;
    private:
        float _space;
};

}

#endif /* VBoxContainer_HPP_ */