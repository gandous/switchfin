
#ifndef SWITCHFIN_HPP_
#define SWITCHFIN_HPP_

#include "gana/App.hpp"
#include "network/JellyfinClient.hpp"

class Switchfin {
    public:
        Switchfin();
        ~Switchfin();

        void run();
    private:
        void on_go_to_home(std::shared_ptr<JellyfinClient> client);
        gana::App _app;
        std::shared_ptr<gana::Node> _current;
};

#endif /* SWITCHFIN_HPP_ */