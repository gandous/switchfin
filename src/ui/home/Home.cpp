
#include "Home.hpp"

Home::Home(std::shared_ptr<JellyfinClient> client): _jclient(client)
{
    set_color(gana::Color(255, 128, 128));
    set_min_size(gana::Vector2f(500, 500));
}

Home::~Home()
{}
