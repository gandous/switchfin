
#ifndef LOGIN_HPP_
#define LOGIN_HPP_

#include "ui/RectContainer.hpp"
#include "ui/box_container/VBoxContainer.hpp"
#include "ui/box_container/HBoxContainer.hpp"
#include "ui/Label.hpp"
#include "ui/LineEdit.hpp"
#include "ui/Button.hpp"
#include "network/JellyfinClient.hpp"

class Login: public gana::RectContainer {
    public:
        Login();
        ~Login();

        void set_client(std::shared_ptr<JellyfinClient> client);
    protected:
        void enter_tree() override;
    private:
        void on_login_pressed();
        void on_login(Request::RCode code, std::string &body);
        void save_data(const std::string &server, const std::string &user, const std::string &password, const std::string &device_id, const std::string &token);
        std::shared_ptr<JellyfinClient> _client;
        std::shared_ptr<LoginRequest> _rlogin;
        gana::VBoxContainer _container;
        gana::Label _lbl_login;
        gana::Label _lbl_name;
        gana::Label _lbl_password;
        gana::LineEdit _le_name;
        gana::LineEdit _le_password;
        gana::Button _btn_login;
        gana::Button _btn_back;
        gana::HBoxContainer _ctn_button;
};

#endif /* LOGIN_HPP_ */