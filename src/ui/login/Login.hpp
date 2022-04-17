
#ifndef LOGIN_HPP_
#define LOGIN_HPP_

#include "ui/RectContainer.hpp"
#include "ui/box_container/VBoxContainer.hpp"
#include "ui/box_container/HBoxContainer.hpp"
#include "ui/Label.hpp"
#include "ui/LineEdit.hpp"
#include "ui/Button.hpp"

class Login: public gana::RectContainer {
    public:
        Login();
        ~Login();

    protected:
        void enter_tree() override;
    private:
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