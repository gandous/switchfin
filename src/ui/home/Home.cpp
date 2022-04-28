
#include "Home.hpp"

Home::Home(std::shared_ptr<JellyfinClient> client): _jclient(client)
{
    set_color(gana::Color(255, 128, 128));
    set_min_size(gana::Vector2f(500, 500));
    _rresume = _jclient->get_resume();
    _rresume->set_callback(Request::mf_callback(*this, &Home::on_resume_receive));
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

void Home::on_resume_receive(Request::RCode code, std::string &body)
{
    gana::Logger::info("%s %s", _rresume->get_error_str().c_str(), body.c_str());
}
