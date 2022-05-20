
#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <memory>
#include "gana/ui/Node.hpp"
#include "gana/ui/NavigationManager.hpp"
#include "gana/ui/MPVPlayer.hpp"
#include "network/JellyfinClient.hpp"

class Player: public gana::Node {
    public:
        Player(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item);
        ~Player();

    protected:
        void process();
    private:
        gana::MPVPlayer _player;
};

#endif /* PLAYER_HPP_ */