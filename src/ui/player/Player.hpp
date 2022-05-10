
#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <memory>
#include "gana/ui/NavigationManager.hpp"
#include "gana/ui/MPVPlayer.hpp"
#include "network/JellyfinClient.hpp"

class Player: public gana::MPVPlayer {
    public:
        Player(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item);
        ~Player();

    private:
};

#endif /* PLAYER_HPP_ */