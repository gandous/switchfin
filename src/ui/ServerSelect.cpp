
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
    std::shared_ptr<gana::Image> bg_img = std::make_shared<gana::Image>();
    bg_img->set_anchor(gana::Node::Anchor::FULL_RECT);
    bg_img->set_image("background_image/rotate4.jpg");
    bg_img->set_stretch_mode(gana::Image::KEEP_ASPECT_COVERED);
    add_child(bg_img);
    std::shared_ptr<gana::ColorRect> bg_img_dark_mask = std::make_shared<gana::ColorRect>();
    bg_img_dark_mask->set_anchor(gana::Node::Anchor::FULL_RECT);
    bg_img_dark_mask->set_color(gana::Color(0, 0, 0, 122));
    add_child(bg_img_dark_mask);
    std::shared_ptr<gana::RectContainer> window = std::make_shared<gana::RectContainer>();
    window->set_color(gana::Color(30, 30, 30, 229));
    window->set_min_size(gana::Vector2f(800, 310));
    window->set_anchor(gana::Node::Anchor::CENTER);
    window->set_content_margin(gana::Rectf(16, 16, 16, 16));
    add_child(window);
    std::shared_ptr<gana::VBoxContainer> container = std::make_shared<gana::VBoxContainer>();
    window->add_child(container);
    std::shared_ptr<gana::Label> lbl_title = std::make_shared<gana::Label>();
    lbl_title->set_text("Switchfin");
    lbl_title->set_hsizing(gana::Node::Sizing::SHRINK_CENTER);
    lbl_title->set_font_size(50);
    container->add_child(lbl_title);
    std::shared_ptr<gana::Node> spacer1 = std::make_shared<gana::Node>();
    spacer1->set_expand();
    container->add_child(spacer1);
    std::shared_ptr<gana::Label> lbl = std::make_shared<gana::Label>();
    lbl->set_font_size(20);
    lbl->set_text("Server address:");
    container->add_child(lbl);
    _server_address = std::make_shared<gana::LineEdit>();
    _server_address->set_min_size(gana::Vector2f(207, 44));
    _server_address->set_hsizing(gana::Node::Sizing::FILL);
    _server_address->set_value("https://");
    container->add_child(_server_address);
    std::shared_ptr<gana::Node> spacer2 = std::make_shared<gana::Node>();
    spacer2->set_expand();
    container->add_child(spacer2);
    std::shared_ptr<gana::Button> button = std::make_shared<gana::Button>();
    button->set_text("Connect");
    button->set_hsizing(gana::Node::Sizing::SHRINK_CENTER);
    button->set_button_type(gana::Button::PRIMARY);
    button->set_min_size(gana::Vector2f(207, 44));
    container->add_child(button);
    std::shared_ptr<gana::Node> spacer3 = std::make_shared<gana::Node>();
    spacer3->set_expand();
    container->add_child(spacer3);
    _server_address->set_bottom_node(button);
    button->set_up_node(_server_address);
}

ServerSelect::~ServerSelect()
{}

void ServerSelect::enter_tree()
{
    _app->set_focused_node(_server_address);
}
