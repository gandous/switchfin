
#ifndef JELLYFINCLIENT_HPP_
#define JELLYFINCLIENT_HPP_

#include <string>
#include <memory>
#include "Http.hpp"
#include "Request.hpp"
#include "PingRequest.hpp"

class JellyfinClient {
    public:
        JellyfinClient(const std::string &url);
        ~JellyfinClient();

        int process();

        std::shared_ptr<PingRequest> ping();
    private:
        std::string _url;
        Http http;
};

#endif /* JELLYFINCLIENT_HPP_ */