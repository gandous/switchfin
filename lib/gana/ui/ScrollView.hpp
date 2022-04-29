
#ifndef SCROLLVIEW_HPP_
#define SCROLLVIEW_HPP_

#include "ui/Node.hpp"

namespace gana {

class ScrollView: public gana::Node {
    public:
        ScrollView();
        ~ScrollView();

        void draw(NVGcontext *ctx) override;
    protected:
        void enter_tree();
    private:
        void on_node_focus(Node *node);
};

}

#endif /* SCROLLVIEW_HPP_ */