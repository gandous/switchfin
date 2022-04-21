
#ifndef SERVERADDRESS_HPP_
#define SERVERADDRESS_HPP_

#include "ui/RectContainer.hpp"
#include "ui/LineEdit.hpp"
#include "type/Signal.hpp"
#include "network/JellyfinClient.hpp"

class ServerAddress: public gana::RectContainer {
    public:
        ServerAddress();
        ~ServerAddress();

        gana::Signal<> go_to_login;
    protected:
        void enter_tree() override;
        void process() override;
    private:
        void connect_pressed();
        gana::LineEdit _server_address;
        std::shared_ptr<JellyfinClient> _client;
        std::shared_ptr<PingRequest> _ping_req;
};

#endif /* SERVERADDRESS_HPP_ */