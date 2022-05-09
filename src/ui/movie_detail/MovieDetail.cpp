
#include "MovieDetail.hpp"

MovieDetail::MovieDetail(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item)
{
    set_anchor(gana::Node::Anchor::FULL_RECT);
    set_color(gana::Color(128, 19, 19));
    // set_color(gana::Color(19, 19, 19));
    set_min_size(gana::Vector2f(500, 500));
}

MovieDetail::~MovieDetail()
{}
