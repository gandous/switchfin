
#include "ServerSelect.hpp"
#include "ui/ColorRect.hpp"
#include "ui/LineEdit.hpp"
#include "ui/Button.hpp"
#include "ui/RectContainer.hpp"
#include "ui/box_container/VBoxContainer.hpp"
#include "ui/Image.hpp"
#include "App.hpp"

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
    gana::RectContainer *window = make_managed<gana::RectContainer>();
    window->set_color(gana::Color(30, 30, 30, 229));
    window->set_min_size(gana::Vector2f(800, 310));
    window->set_anchor(gana::Node::Anchor::CENTER);
    window->set_content_margin(gana::Rectf(16, 16, 16, 16));
    add_child(window);
    gana::VBoxContainer *container = make_managed<gana::VBoxContainer>();
    window->add_child(container);
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
    container->add_child(button);
    gana::Node *spacer3 = make_managed<gana::Node>();
    spacer3->set_expand();
    container->add_child(spacer3);
    _server_address.set_bottom_node(button);
    button->set_up_node(&_server_address);
}

ServerSelect::~ServerSelect()
{}

void ServerSelect::enter_tree()
{
    _app->set_focused_node(&_server_address);
}
