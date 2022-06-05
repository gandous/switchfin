
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

        gana::Signal<std::shared_ptr<JellyfinClient>> signal_go_to_home;
    protected:
    private:
        void on_go_to_login();
        void on_login_success();
        ServerAddress _server_address;
        Login _login;
};

#endif /* SERVERSELECT_HPP_ */