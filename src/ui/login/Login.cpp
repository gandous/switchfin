
#include "simpleini/SimpleIni.hpp"
#include "App.hpp"
#include "AssetManager.hpp"
#include "config.hpp"
#include "Login.hpp"

Login::Login()
{
    set_color(gana::Color(30, 30, 30, 229));
    set_min_size(gana::Vector2f(800, 310));
    set_anchor(gana::Node::Anchor::CENTER);
    set_content_margin(gana::Rectf(16, 16, 16, 16));
    _container.set_anchor(gana::Node::Anchor::FULL_RECT);
    add_child(&_container);
    _lbl_login.set_text("Login");
    _lbl_login.set_font_size(50);
    _lbl_login.set_hsizing(gana::Node::Sizing::SHRINK_CENTER);
    _container.add_child(&_lbl_login);

    _container.add_spacer(16, true);
    _lbl_name.set_text("Name:");
    _container.add_child(&_lbl_name);

    _le_name.set_hsizing(gana::Node::Sizing::FILL);
    _le_name.set_bottom_node(&_le_password);
    _le_name.set_min_size(gana::Vector2f(207, 44));
    _container.add_child(&_le_name);

    _container.add_spacer();
    _lbl_password.set_text("Password:");
    _container.add_child(&_lbl_password);

    _le_password.set_hsizing(gana::Node::Sizing::FILL);
    _le_password.set_top_node(&_le_name);
    _le_password.set_bottom_node(&_btn_login);
    _le_password.set_min_size(gana::Vector2f(207, 44));
    _container.add_child(&_le_password);

    _container.add_spacer(16, true);
    _ctn_button.set_hsizing(gana::Node::Sizing::FILL);
    _container.add_child(&_ctn_button);

    _ctn_button.add_spacer(32, true);
    _btn_back.set_min_size(gana::Vector2f(207, 44));
    _btn_back.set_text("Cancel");
    _btn_back.set_top_node(&_le_password);
    _btn_back.set_right_node(&_btn_login);
    _ctn_button.add_child(&_btn_back);

    _ctn_button.add_spacer(16, true);
    _btn_login.set_button_type(gana::Button::PRIMARY);
    _btn_login.set_min_size(gana::Vector2f(207, 44));
    _btn_login.set_text("Login");
    _btn_login.set_top_node(&_le_password);
    _btn_login.set_left_node(&_btn_back);
    _btn_login.signal_pressed.connect(*this, &Login::on_login_pressed);
    _ctn_button.add_child(&_btn_login);
    _ctn_button.add_spacer(32, true);

    _lbl_connecting.set_text("Connecting");
    _lbl_connecting.set_anchor(gana::Node::Anchor::CENTER);
    add_child(&_lbl_connecting);
    show_connecting(false);
}

Login::~Login()
{}

void Login::set_client(std::shared_ptr<JellyfinClient> client)
{
    _client = client;
}

void Login::enter_tree()
{
    _app->set_focused_node(&_le_name);
    set_process(true);
}

void Login::process()
{
    if (_client != nullptr)
        _client->process();
}

void Login::on_login_pressed()
{
    show_connecting(true);
    _rlogin = _client->login(_le_name.get_text(), _le_password.get_text());
    _rlogin->set_callback(gana::Request::mf_callback(*this, &Login::on_login));
}

void Login::on_login(gana::Request::RCode code)
{
    if (code == gana::Request::OK) {
        gana::Logger::info("Login success");
        save_data(_client->get_url(), _le_name.get_text(), "id", _rlogin->get_token(), _rlogin->get_user_id());
        _client->set_user_id(_rlogin->get_user_id());
        _client->set_token(_rlogin->get_token());
        signal_login_success.emit();
    } else {
        gana::Logger::error("Login failed (code: %d)", code);
        show_connecting(false);
    }
}

void Login::save_data(const std::string &server, const std::string &user, const std::string &device_id, const std::string &token, const std::string &user_id)
{
    CSimpleIni ini;

    ini.SetValue("SERVER", "address", server.c_str());
    ini.SetValue("SERVER", "user", user.c_str());
    ini.SetValue("SERVER", "device_id", device_id.c_str());
    ini.SetValue("SERVER", "token", token.c_str());
    ini.SetValue("SERVER", "user_id", user_id.c_str());
    FILE *f = fopen(SERVER_CONFIG_PATH, "w+");
    ini.SetSpaces(false);
    ini.SaveFile(f);
    fclose(f);
    gana::Logger::info("Server info saved");
}

void Login::show_connecting(bool visibility)
{
    _lbl_connecting.set_visible(visibility);
    _lbl_name.set_visible(!visibility);
    _lbl_password.set_visible(!visibility);
    _le_name.set_visible(!visibility);
    _le_password.set_visible(!visibility);
    _btn_login.set_visible(!visibility);
    _btn_back.set_visible(!visibility);
}
