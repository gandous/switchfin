
#ifndef SERVERSELECT_HPP_
#define SERVERSELECT_HPP_

#include "ui/Node.hpp"
#include "ServerAddress.hpp"

class ServerSelect: public gana::Node {
    public:
        ServerSelect();
        ~ServerSelect();

    protected:
    private:
        ServerAddress _server_address;
        void on_go_to_login();
};

#endif /* SERVERSELECT_HPP_ */