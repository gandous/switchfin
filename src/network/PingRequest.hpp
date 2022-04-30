
#ifndef PINGREQUEST_HPP_
#define PINGREQUEST_HPP_

#include "network/Request.hpp"

class PingRequest: public gana::Request {
    public:
        PingRequest();
        ~PingRequest();

    protected:
        void parse();
    private:
};

#endif /* PINGREQUEST_HPP_ */