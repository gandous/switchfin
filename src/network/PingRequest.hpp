
#ifndef PINGREQUEST_HPP_
#define PINGREQUEST_HPP_

#include "Request.hpp"

class PingRequest: public Request {
    public:
        PingRequest();
        ~PingRequest();

    protected:
        void parse();
    private:
};

#endif /* PINGREQUEST_HPP_ */