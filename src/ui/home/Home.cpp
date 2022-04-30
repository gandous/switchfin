
#include "ui/ScrollView.hpp"
#include "ui/ColorRect.hpp"
#include "App.hpp"
#include "Home.hpp"

Home::Home(std::shared_ptr<JellyfinClient> client): _jclient(client)
{
    set_color(gana::Color(255, 128, 128));
    set_min_size(gana::Vector2f(500, 500));
    _rresume = _jclient->get_resume();
    _rresume->set_callback(gana::Request::mf_callback(*this, &Home::on_resume_receive));

    gana::ScrollView *scroll = make_managed<gana::ScrollView>();
    scroll->set_size(gana::Vector2f(700, 520));
    add_child(scroll);

    gana::ColorRect *rect;
    rect = make_managed<gana::ColorRect>();
    rect->set_min_size(gana::Vector2f(500, 500));
    rect->set_color(gana::Color(255, 0, 0));
    _ctn_main.add_child(rect);
    rect = make_managed<gana::ColorRect>();
    rect->set_min_size(gana::Vector2f(500, 500));
    rect->set_color(gana::Color(0, 255, 0));
    _ctn_main.add_child(rect);
    rect = make_managed<gana::ColorRect>();
    rect->set_min_size(gana::Vector2f(500, 500));
    rect->set_color(gana::Color(0, 0, 255));
    _ctn_main.add_child(rect);
    scroll->add_child(&_ctn_main);
    _ctn_main.set_anchor(gana::Node::Anchor::CENTER_LEFT);

    add_child(&_img_test);
    _img_test.set_min_size(gana::Vector2f(500, 500));
    _img_test.set_image(_jclient->get_http(), "https://jellyfin.gama.ovh/Items/d3e58ca1a18662ffc877e4c61869ac79/Images/Backdrop?fillHeight=200&fillWidth=355&quality=96&tag=bb27624f1a9b0722b2efdee2ed680d6d");
}

Home::~Home()
{}

void Home::enter_tree()
{
    set_process(true);
    _app->set_focused_node(&_ctn_main);
}

void Home::process()
{
    _jclient->process();
}

void Home::on_resume_receive(gana::Request::RCode code, gana::Request &req)
{
    gana::Logger::info("%s %s", _rresume->get_error_str().c_str(), req.get_body_as_string().c_str());
    for (auto &item: _rresume->get_items())
        gana::Logger::info("Name: %s", item.get_name().c_str());
}
