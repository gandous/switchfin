
#ifndef HBOXCONTAINER_HPP_
#define HBOXCONTAINER_HPP_

#include "ui/Node.hpp"

namespace gana {

class HBoxContainer: public Node {
    public:
        HBoxContainer();
        ~HBoxContainer();

        void update_layout(const Vector2f &size) override;
        Vector2f get_min_size() override;
    private:
};

}

#endif /* HBOXCONTAINER_HPP_ */