
#ifndef PINGRESPONSE_HPP_
#define PINGRESPONSE_HPP_

#include "Response.hpp"

class PingResponse: public Response {
    public:
        PingResponse(int code, const std::string &data);
        ~PingResponse();

    private:
};

#endif /* PINGRESPONSE_HPP_ */