
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
        std::shared_ptr<gana::Node> _current;
};

#endif /* SWITCHFIN_HPP_ */