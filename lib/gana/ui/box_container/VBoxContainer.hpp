
#ifndef VBoxContainer_HPP_
#define VBoxContainer_HPP_

#include "ui/Node.hpp"

namespace gana {

class VBoxContainer: public Node {
    public:
        VBoxContainer();
        ~VBoxContainer();

        void update_layout(const Vector2f &size) override;
        Vector2f get_min_size() override;
        void add_spacer(float h = 16, bool expand = false);
    private:
};

}

#endif /* VBoxContainer_HPP_ */