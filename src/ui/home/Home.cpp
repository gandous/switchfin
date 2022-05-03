
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

    _ctn_main.set_anchor(gana::Node::Anchor::FULL_RECT);
    _ctn_main.add_spacer(16);
    add_child(&_ctn_main);

    _lbl_continue_watching.set_text("Continue watching");
    _ctn_main.add_child(&_lbl_continue_watching);

    gana::ScrollView *scroll = _ctn_main.make_managed<gana::ScrollView>();
    scroll->set_min_size(gana::Vector2f(700, 400));
    _ctn_main.add_child(scroll);

    // gana::ColorRect *rect;
    // rect = make_managed<gana::ColorRect>();
    // rect->set_min_size(gana::Vector2f(500, 500));
    // rect->set_color(gana::Color(255, 0, 0));
    // _ctn_main.add_child(rect);
    // rect = make_managed<gana::ColorRect>();
    // rect->set_min_size(gana::Vector2f(500, 500));
    // rect->set_color(gana::Color(0, 255, 0));
    // _ctn_main.add_child(rect);
    // rect = make_managed<gana::ColorRect>();
    // rect->set_min_size(gana::Vector2f(500, 500));
    // rect->set_color(gana::Color(0, 0, 255));
    // _ctn_main.add_child(rect);
    _ctn_resume_movie.set_space(16);
    scroll->add_child(&_ctn_resume_movie);
}

Home::~Home()
{}

void Home::enter_tree()
{
    set_process(true);
}

void Home::process()
{
    _jclient->process();
}

void Home::on_resume_receive(gana::Request::RCode code, gana::Request &req)
{
    gana::Logger::info("%s %s", _rresume->get_error_str().c_str(), req.get_body_as_string().c_str());
    for (auto &item: _rresume->get_items()) {
        BigMovieVignette *vign = _ctn_resume_movie.make_managed<BigMovieVignette>(_jclient->get_http(), _jclient->get_img_url(item.get_id(), JellyfinClient::BACKDROP));
        gana::Logger::info("Name: %s", item.get_name().c_str());
        _ctn_resume_movie.add_child(vign);
    }
    _app->set_focused_node(&_ctn_resume_movie);
}
