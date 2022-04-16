
#ifndef SERVERSELECT_HPP_
#define SERVERSELECT_HPP_

#include "ui/Node.hpp"
#include "ui/LineEdit.hpp"

class ServerSelect: public gana::Node {
    public:
        ServerSelect();
        ~ServerSelect();

    protected:
        void enter_tree();
    private:
        std::shared_ptr<gana::LineEdit> _server_address;
};

#endif /* SERVERSELECT_HPP_ */