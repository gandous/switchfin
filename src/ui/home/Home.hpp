
#ifndef HOME_HPP_
#define HOME_HPP_

#include <memory>
#include "network/JellyfinClient.hpp"
#include "ui/ColorRect.hpp"

class Home: public gana::ColorRect {
    public:
        Home(std::shared_ptr<JellyfinClient> client);
        ~Home();

    protected:
        void enter_tree() override;
        void process() override;
    private:
        void on_resume_receive(Request::RCode code, std::string &body);
        std::shared_ptr<JellyfinClient> _jclient;
        std::shared_ptr<Items> _rresume;
};

#endif /* HOME_HPP_ */