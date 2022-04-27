
#ifndef SERVERADDRESS_HPP_
#define SERVERADDRESS_HPP_

#include "ui/RectContainer.hpp"
#include "ui/LineEdit.hpp"
#include "ui/Label.hpp"
#include "type/Signal.hpp"
#include "ui/LineEdit.hpp"
#include "ui/Button.hpp"
#include "ui/box_container/VBoxContainer.hpp"
#include "network/JellyfinClient.hpp"

class ServerAddress: public gana::RectContainer {
    public:
        ServerAddress();
        ~ServerAddress();

        gana::Signal<> go_to_login;
        std::shared_ptr<JellyfinClient> get_client();
    protected:
        void enter_tree() override;
        void process() override;
    private:
        void connect_pressed();
        void on_ping_response(Request::RCode code, std::string &body);
        void show_connecting(bool visibility);
        gana::LineEdit _le_server_address;
        gana::Label _lbl_error;
        gana::Label _lbl_title;
        gana::Label _lbl_connecting;
        gana::Label _lbl_server_addr;
        gana::Button _btn_connect;
        gana::VBoxContainer _ctn_main;
        std::shared_ptr<JellyfinClient> _client;
        std::shared_ptr<PingRequest> _ping_req;
};

#endif /* SERVERADDRESS_HPP_ */