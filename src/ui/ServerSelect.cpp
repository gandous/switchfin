
#include "ServerSelect.hpp"
#include "ui/ColorRect.hpp"
#include "ui/LineEdit.hpp"
#include "ui/Button.hpp"
#include "ui/RectContainer.hpp"
#include "ui/box_container/VBoxContainer.hpp"

ServerSelect::ServerSelect()
{
    std::shared_ptr<gana::ColorRect> rect = std::make_shared<gana::ColorRect>();
    rect->set_color(gana::Color(30, 30, 30));
    rect->set_anchor(gana::Node::Anchor::FULL_RECT);
    add_child(rect);
    std::shared_ptr<gana::RectContainer> window = std::make_shared<gana::RectContainer>();
    window->set_color(gana::Color(16, 16, 16));
    window->set_min_size(gana::Vector2f(800, 200));
    window->set_anchor(gana::Node::Anchor::CENTER);
    window->set_content_margin(gana::Rectf(16, 16, 16, 16));
    add_child(window);
    std::shared_ptr<gana::VBoxContainer> container = std::make_shared<gana::VBoxContainer>();
    window->add_child(container);
    std::shared_ptr<gana::Label> lbl_title = std::make_shared<gana::Label>();
    lbl_title->set_text("Switchfin");
    lbl_title->set_hsizing(gana::Node::Sizing::SHRINK_CENTER);
    lbl_title->set_font_size(40);
    container->add_child(lbl_title);
    std::shared_ptr<gana::Label> lbl = std::make_shared<gana::Label>();
    lbl->set_text("Enter server address:");
    container->add_child(lbl);
    std::shared_ptr<gana::LineEdit> server_address = std::make_shared<gana::LineEdit>();
    server_address->set_hsizing(gana::Node::Sizing::FILL);
    server_address->set_value("https://");
    container->add_child(server_address);
    std::shared_ptr<gana::Button> button = std::make_shared<gana::Button>();
    button->set_text("Connect");
    button->set_hsizing(gana::Node::Sizing::SHRINK_CENTER);
    container->add_child(button);
}

ServerSelect::~ServerSelect()
{}
