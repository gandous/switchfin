
#include "Player.hpp"

Player::Player(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item)
{
    set_source(client->get_stream_url(item.get_id()));
}

Player::~Player()
{}
