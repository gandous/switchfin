
#ifndef SWITCHFIN_HPP_
#define SWITCHFIN_HPP_

#include "gana/App.hpp"
#include "ui/login/ServerSelect.hpp"

#include "ui/MPVPlayer.hpp"
class Switchfin {
    public:
        Switchfin();
        ~Switchfin();

        void run();
    private:
        gana::App _app;
        // ServerSelect _server_select;
        gana::MPVPlayer _player;
};

#endif /* SWITCHFIN_HPP_ */