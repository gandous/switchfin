
#include "App.hpp"
#include "ServerAddress.hpp"

ServerAddress::ServerAddress()
{
    set_color(gana::Color(30, 30, 30, 229));
    set_min_size(gana::Vector2f(800, 310));
    set_anchor(gana::Node::Anchor::CENTER);
    set_content_margin(gana::Rectf(16, 16, 16, 16));
    add_child(&_ctn_main);
    _lbl_title.set_text("Switchfin");
    _lbl_title.set_hsizing(gana::Node::Sizing::SHRINK_CENTER);
    _lbl_title.set_font_size(50);
    _ctn_main.add_child(&_lbl_title);
    _ctn_main.add_spacer(8, true);
    _lbl_server_addr.set_font_size(20);
    _lbl_server_addr.set_text("Server address:");
    _ctn_main.add_child(&_lbl_server_addr);
    _le_server_address.set_min_size(gana::Vector2f(207, 44));
    _le_server_address.set_hsizing(gana::Node::Sizing::FILL);
    _le_server_address.set_value("https://");
    _ctn_main.add_child(&_le_server_address);
    _ctn_main.add_spacer(8, true);
    _lbl_error.set_preset(gana::Label::ERROR);
    _lbl_error.set_hsizing(gana::Node::Sizing::SHRINK_CENTER);
    _ctn_main.add_child(&_lbl_error);
    _ctn_main.add_spacer(8, true);
    _btn_connect.set_text("Connect");
    _btn_connect.set_hsizing(gana::Node::Sizing::SHRINK_CENTER);
    _btn_connect.set_button_type(gana::Button::PRIMARY);
    _btn_connect.set_min_size(gana::Vector2f(207, 44));
    _btn_connect.signal_pressed.connect(*this, &ServerAddress::connect_pressed);
    _ctn_main.add_child(&_btn_connect);
    _ctn_main.add_spacer(8, true);
    _le_server_address.set_bottom_node(&_btn_connect);
    _btn_connect.set_top_node(&_le_server_address);

    _lbl_connecting.set_text("Connecting");
    set_anchor(gana::Node::Anchor::CENTER);
    add_child(&_lbl_connecting);
    show_connecting(false);
}

ServerAddress::~ServerAddress()
{}

std::shared_ptr<JellyfinClient> ServerAddress::get_client()
{
    return (_client);
}

void ServerAddress::enter_tree()
{
    _app->set_focused_node(&_le_server_address);
    set_process(true);
}

void ServerAddress::process()
{
    if (_client != nullptr)
        _client->process();
}

void ServerAddress::connect_pressed()
{
    _client = std::make_shared<JellyfinClient>(_le_server_address.get_text());

    show_connecting(true);
    _ping_req = _client->ping();
    _ping_req->set_callback(gana::Request::mf_callback(*this, &ServerAddress::on_ping_response));
}

void ServerAddress::on_ping_response(gana::Request::RCode code)
{
    gana::Logger::info("%d %s", code, _ping_req->get_body_as_string().c_str());
    if (code != gana::Request::OK) {
        _lbl_error.set_text(_ping_req->get_error_str());
        show_connecting(false);
    } else {
        go_to_login.emit();
    }
}

void ServerAddress::show_connecting(bool visibility)
{
    _lbl_connecting.set_visible(visibility);
    _lbl_error.set_visible(!visibility);
    _lbl_server_addr.set_visible(!visibility);
    _btn_connect.set_visible(!visibility);
    _le_server_address.set_visible(!visibility);
}
