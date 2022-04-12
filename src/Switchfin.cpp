
#include "Switchfin.hpp"
#include "ui/ColorRect.hpp"
#include "ui/Node.hpp"
#include "ui/box_container/HBoxContainer.hpp"

std::shared_ptr<gana::Node> add_rect(std::shared_ptr<gana::Node> parent)
{
    std::shared_ptr<gana::ColorRect> rect = std::make_shared<gana::ColorRect>();
    std::shared_ptr<gana::ColorRect> rect2 = std::make_shared<gana::ColorRect>();
    std::shared_ptr<gana::ColorRect> rect3 = std::make_shared<gana::ColorRect>();
    std::shared_ptr<gana::HBoxContainer> container = std::make_shared<gana::HBoxContainer>();
    rect->set_min_size(gana::Vector2f(200, 200));
    rect->set_color(gana::Color(255, 0, 0));
    rect2->set_min_size(gana::Vector2f(200, 200));
    rect2->set_color(gana::Color(0, 255, 0));
    rect3->set_min_size(gana::Vector2f(200, 100));
    rect3->set_color(gana::Color(0, 0, 255));
    rect->set_expand();
    rect2->set_expand();
    parent->add_child(container);
    container->add_child(rect);
    container->add_child(rect3);
    container->add_child(rect2);
    return (container);
}

Switchfin::Switchfin(): _app("Switchfin")
{
}

Switchfin::~Switchfin()
{
}

void Switchfin::run()
{
    std::shared_ptr<gana::Node> node = std::make_shared<gana::Node>();
    // std::shared_ptr<gana::HBoxContainer> container = std::make_shared<gana::HBoxContainer>();
    // std::shared_ptr<gana::Node> c1 = add_rect(container);
    // add_rect(container);
    // c1->set_expand(true);
    // node->add_child(container);
    // container->set_size(gana::Vector2f(1500, 200));
    std::shared_ptr<gana::ColorRect> rect = std::make_shared<gana::ColorRect>();
    rect->set_min_size(gana::Vector2f(200, 200));
    rect->set_color(gana::Color(255, 0, 0));
    rect->set_layout_mode(gana::Node::ANCHOR);
    rect->set_anchor(gana::Node::BOTTOM_WIDE);
    node->add_child(rect);
    _app.set_root_node(node);
    _app.run();
}