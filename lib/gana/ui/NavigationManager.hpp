
#ifndef NAVIGATIONMANAGER_HPP_
#define NAVIGATIONMANAGER_HPP_

#include <stack>
#include <memory>
#include "ui/Node.hpp"

namespace gana {

class NavigationManager: public Node {
    public:
        NavigationManager();
        ~NavigationManager();

        void process_event(Event &evt) override;
        void navigate_up();
        template<typename T, typename ...ARGS>
        void navigate_down(ARGS&& ...args)
        {
            std::shared_ptr<Node> node = std::make_shared<T>(*this, args...);
            if (_stack.size() > 0)
                remove_child(_stack.top().get());
            add_child(node.get());
            _stack.push(node);
        }
    private:
        std::stack<std::shared_ptr<Node>> _stack;
};

}

#endif /* NAVIGATIONMANAGER_HPP_ */