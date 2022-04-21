
#include "ServerSelect.hpp"
#include "ui/ColorRect.hpp"
#include "ui/LineEdit.hpp"
#include "ui/Button.hpp"
#include "ui/RectContainer.hpp"
#include "ui/box_container/VBoxContainer.hpp"
#include "ui/Image.hpp"

ServerSelect::ServerSelect()
{
    gana::Image *bg_img = make_managed<gana::Image>();
    bg_img->set_anchor(gana::Node::Anchor::FULL_RECT);
    bg_img->set_image("background_image/rotate4.jpg");
    bg_img->set_stretch_mode(gana::Image::KEEP_ASPECT_COVERED);
    add_child(bg_img);
    gana::ColorRect *bg_img_dark_mask = make_managed<gana::ColorRect>();
    bg_img_dark_mask->set_anchor(gana::Node::Anchor::FULL_RECT);
    bg_img_dark_mask->set_color(gana::Color(0, 0, 0, 122));
    add_child(bg_img_dark_mask);
    add_child(&_server_address);
    _server_address.go_to_login.connect(*this, &ServerSelect::on_go_to_login);
}

ServerSelect::~ServerSelect()
{}

void ServerSelect::on_go_to_login()
{
    remove_child(&_server_address);
    _login.set_client(_server_address.get_client());
    add_child(&_login);
}
