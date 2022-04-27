
#ifndef JELLYFINCLIENT_HPP_
#define JELLYFINCLIENT_HPP_

#include <string>
#include <memory>
#include "Http.hpp"
#include "Request.hpp"
#include "PingRequest.hpp"
#include "LoginRequest.hpp"

class JellyfinClient {
    public:
        JellyfinClient(const std::string &url);
        ~JellyfinClient();

        int process();

        const std::string &get_url() const;
        std::shared_ptr<PingRequest> ping();
        std::shared_ptr<LoginRequest> login(const std::string &name, const std::string &password);
    private:
        std::string _url;
        Http http;
};

#endif /* JELLYFINCLIENT_HPP_ */