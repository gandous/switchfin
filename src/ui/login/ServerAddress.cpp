
#include <curl/curl.h>
#include "ui/LineEdit.hpp"
#include "ui/Button.hpp"
#include "ui/box_container/VBoxContainer.hpp"
#include "App.hpp"
#include "ServerAddress.hpp"

ServerAddress::ServerAddress()
{
    set_color(gana::Color(30, 30, 30, 229));
    set_min_size(gana::Vector2f(800, 310));
    set_anchor(gana::Node::Anchor::CENTER);
    set_content_margin(gana::Rectf(16, 16, 16, 16));
    gana::VBoxContainer *container = make_managed<gana::VBoxContainer>();
    add_child(container);
    gana::Label *lbl_title = make_managed<gana::Label>();
    lbl_title->set_text("Switchfin");
    lbl_title->set_hsizing(gana::Node::Sizing::SHRINK_CENTER);
    lbl_title->set_font_size(50);
    container->add_child(lbl_title);
    gana::Node *spacer1 = make_managed<gana::Node>();
    spacer1->set_expand();
    container->add_child(spacer1);
    gana::Label *lbl = make_managed<gana::Label>();
    lbl->set_font_size(20);
    lbl->set_text("Server address:");
    container->add_child(lbl);
    _server_address.set_min_size(gana::Vector2f(207, 44));
    _server_address.set_hsizing(gana::Node::Sizing::FILL);
    _server_address.set_value("https://");
    container->add_child(&_server_address);
    gana::Node *spacer2 = make_managed<gana::Node>();
    spacer2->set_expand();
    container->add_child(spacer2);
    gana::Button *button = make_managed<gana::Button>();
    button->set_text("Connect");
    button->set_hsizing(gana::Node::Sizing::SHRINK_CENTER);
    button->set_button_type(gana::Button::PRIMARY);
    button->set_min_size(gana::Vector2f(207, 44));
    button->signal_pressed.connect(*this, &ServerAddress::connect_pressed);
    container->add_child(button);
    gana::Node *spacer3 = make_managed<gana::Node>();
    spacer3->set_expand();
    container->add_child(spacer3);
    _server_address.set_bottom_node(button);
    button->set_up_node(&_server_address);

}

ServerAddress::~ServerAddress()
{}

void ServerAddress::enter_tree()
{
    _app->set_focused_node(&_server_address);
    set_process(true);
}

void ServerAddress::process()
{
    if (_client != nullptr)
        _client->process();
}

void ServerAddress::connect_pressed()
{
    _client = std::make_shared<JellyfinClient>("https://jellyfin.gama.ovh");

    _client->ping([](PingResponse &resp){
        std::cout << "Callback: "  << (int)(resp.get_error()) << std::endl;
    });
}
