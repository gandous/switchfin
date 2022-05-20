
#include "Player.hpp"

Player::Player(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item)
{
    _player.set_source(client->get_stream_url(item.get_id()));
    add_child(&_player);
    set_process();
}

Player::~Player()
{}

void Player::process()
{
    gana::Logger::info("time pos %d/%d", _player.get_time_pos(), _player.get_duration());
}
