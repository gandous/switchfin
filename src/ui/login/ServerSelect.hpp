
#ifndef SERVERSELECT_HPP_
#define SERVERSELECT_HPP_

#include "ui/Node.hpp"
#include "ServerAddress.hpp"
#include "Login.hpp"
#include "ui/Label.hpp"

class ServerSelect: public gana::Node {
    public:
        ServerSelect();
        ~ServerSelect();

    protected:
    private:
        ServerAddress _server_address;
        Login _login;
        void on_go_to_login();
};

#endif /* SERVERSELECT_HPP_ */