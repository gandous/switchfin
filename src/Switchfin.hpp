
#ifndef SWITCHFIN_HPP_
#define SWITCHFIN_HPP_

#include "gana/App.hpp"

class Switchfin {
    public:
        Switchfin();
        ~Switchfin();

        void run();
    private:
        gana::App _app;
};

#endif /* SWITCHFIN_HPP_ */