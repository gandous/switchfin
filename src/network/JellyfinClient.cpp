
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
    http.get(req, _url + "/System/Ping");
    return (req);
};

std::shared_ptr<LoginRequest> JellyfinClient::login(const std::string &name, const std::string &password)
{
    Http::Headers headers = {
        {"X-Emby-Authorization", "MediaBrowser Client=\"Jellyfin Web\", Device=\"Firefox\", DeviceId=\"TW96aWxsYS81LjAgKFgxMTsgRmVkb3JhOyBMaW51eCB4ODZfNjQ7IHJ2Ojk4LjApIEdlY2tvLzIwMTAwMTAxIEZpcmVmb3gvOTguMHwxNjUwMjM4ODU5MjQx\", Version=\"10.7.6\""},
        {"Content-Type", "application/json"}
    };
    std::shared_ptr<LoginRequest> req = std::make_shared<LoginRequest>();
    http.post(req, _url + "/Users/authenticatebyname", "{\"Username\":\"" + name + "\",\"Pw\":\"" + password + "\"}", headers);
    return (req);
}
