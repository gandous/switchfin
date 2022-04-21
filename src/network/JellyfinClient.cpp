
#include "JellyfinClient.hpp"

JellyfinClient::JellyfinClient(const std::string &url): _url(url)
{}

JellyfinClient::~JellyfinClient()
{}

int JellyfinClient::process()
{
    return (http.process());
}

std::shared_ptr<PingRequest> JellyfinClient::ping()
{
    std::shared_ptr<PingRequest> req = std::make_shared<PingRequest>();
    http.get(req, _url + "/System/Ping", "");
    return (req);
};