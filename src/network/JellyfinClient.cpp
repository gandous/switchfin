
#include "JellyfinClient.hpp"

JellyfinClient::JellyfinClient(const std::string &url): _url(url)
{}

JellyfinClient::~JellyfinClient()
{}

int JellyfinClient::process()
{
    return (http.process());
}

void JellyfinClient::ping(std::function<void(PingResponse &)> callback)
{
    http.get(_url + "/System/Ping", "", [callback](int code, std::string body){
        PingResponse resp(code, body);
        callback(resp);
    });
};