
#include <sstream>
#include "config.hpp"
#include "JellyfinClient.hpp"

JellyfinClient::JellyfinClient(const std::string &url): _url(url)
{}

JellyfinClient::~JellyfinClient()
{}

void JellyfinClient::set_token(const std::string &token)
{
    _token = token;
    update_default_header();
}

void JellyfinClient::set_user_id(const std::string &id)
{
    _user_id = id;
}

int JellyfinClient::process()
{
    return (_http.process());
}

const std::string &JellyfinClient::get_url() const
{
    return (_url);
}

std::shared_ptr<PingRequest> JellyfinClient::ping()
{
    std::shared_ptr<PingRequest> req = std::make_shared<PingRequest>();
    _http.get(req, _url + "/System/Ping");
    return (req);
};

std::shared_ptr<LoginRequest> JellyfinClient::login(const std::string &name, const std::string &password)
{
    Http::Headers headers = {
        {"X-Emby-Authorization", "MediaBrowser Client=\"Jellyfin Web\", Device=\"Firefox\", DeviceId=\"TW96aWxsYS81LjAgKFgxMTsgRmVkb3JhOyBMaW51eCB4ODZfNjQ7IHJ2Ojk4LjApIEdlY2tvLzIwMTAwMTAxIEZpcmVmb3gvOTguMHwxNjUwMjM4ODU5MjQx\", Version=\"10.7.6\""},
        {"Content-Type", "application/json"}
    };
    std::shared_ptr<LoginRequest> req = std::make_shared<LoginRequest>();
    _http.post(req, _url + "/Users/authenticatebyname", "{\"Username\":\"" + name + "\",\"Pw\":\"" + password + "\"}", headers);
    return (req);
}

std::shared_ptr<Items> JellyfinClient::get_resume()
{
    std::ostringstream url;
    Http::UrlParams params = {
        {"MediaTypes", "Video"}
    };

    url << _url << "/Users/" << _user_id << "/Items/Resume";
    std::shared_ptr<Items> req = std::make_shared<Items>();
    _http.get(req, url.str(), _default_header);
    return (req);
}

void JellyfinClient::update_default_header()
{
    std::ostringstream emby_auth;

    emby_auth << "MediaBrowser Client=\"" << CLIENT_NAME << "\", Device=\"" << DEVICE_NAME << "\", Token=" << _token;
    _default_header["X-Emby-Authorization"] = emby_auth.str();
    _default_header["Content-Type"] = "application/json";
}
