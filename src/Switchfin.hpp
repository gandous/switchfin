
#ifndef SWITCHFIN_HPP_
#define SWITCHFIN_HPP_

#include "gana/App.hpp"
#include "ui/login/ServerSelect.hpp"

class Switchfin {
    public:
        Switchfin();
        ~Switchfin();

        void run();
    private:
        gana::App _app;
        ServerSelect _server_select;
};

#endif /* SWITCHFIN_HPP_ */