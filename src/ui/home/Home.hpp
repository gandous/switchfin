
#ifndef HOME_HPP_
#define HOME_HPP_

#include <memory>
#include "network/JellyfinClient.hpp"
#include "ui/ColorRect.hpp"

class Home: public gana::ColorRect {
    public:
        Home(std::shared_ptr<JellyfinClient> client);
        ~Home();

    private:
        std::shared_ptr<JellyfinClient> _jclient;
};

#endif /* HOME_HPP_ */