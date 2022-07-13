
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

gana::Http &JellyfinClient::get_http()
{
    return (_http);
}

std::shared_ptr<PingRequest> JellyfinClient::ping()
{
    std::shared_ptr<PingRequest> req = std::make_shared<PingRequest>();
    _http.get(req, _url + "/System/Ping");
    return (req);
};

std::shared_ptr<LoginRequest> JellyfinClient::login(const std::string &name, const std::string &password)
{
    gana::Http::Headers headers = {
        {"X-Emby-Authorization", "MediaBrowser Client=\"Jellyfin Web\", Device=\"Firefox\", DeviceId=\"TW96aWxsYS81LjAgKFgxMTsgRmVkb3JhOyBMaW51eCB4ODZfNjQ7IHJ2Ojk4LjApIEdlY2tvLzIwMTAwMTAxIEZpcmVmb3gvOTguMHwxNjUwMjM4ODU5MjQx\", Version=\"10.7.6\""},
        {"Content-Type", "application/json"}
    };
    std::shared_ptr<LoginRequest> req = std::make_shared<LoginRequest>();
    _http.post(req, _url + "/Users/authenticatebyname", "{\"Username\":\"" + name + "\",\"Pw\":\"" + password + "\"}", headers);
    return (req);
}

std::shared_ptr<ItemsRequest> JellyfinClient::get_resume()
{
    std::ostringstream url;
    gana::Http::UrlParams params = {
        {"MediaTypes", "Video"}
    };

    url << _url << "/Users/" << _user_id << "/Items/Resume";
    std::shared_ptr<ItemsRequest> req = std::make_shared<ItemsRequest>();
    _http.get(req, url.str(), _default_header, params);
    return (req);
}

std::shared_ptr<ItemsRequest> JellyfinClient::get_views()
{
    std::ostringstream url;

    url << _url << "/Users/" << _user_id << "/Views";
    std::shared_ptr<ItemsRequest> req = std::make_shared<ItemsRequest>();
    _http.get(req, url.str(), _default_header);
    return (req);
}

std::shared_ptr<ItemListRequest> JellyfinClient::get_latest(const std::string &parent_id)
{
    std::ostringstream url;
    gana::Http::UrlParams params = {
        {"ParentId", parent_id},
        {"Limit", "16"}
    };

    url << _url << "/Users/" << _user_id << "/Items/Latest";
    std::shared_ptr<ItemListRequest> req = std::make_shared<ItemListRequest>();
    _http.get(req, url.str(), _default_header, params);
    return (req);
}

std::shared_ptr<ItemRequest> JellyfinClient::get_info(const std::string &id)
{
    std::ostringstream url;

    url << _url << "/Users/" << _user_id << "/Items/" << id;
    std::shared_ptr<ItemRequest> req = std::make_shared<ItemRequest>();
    _http.get(req, url.str(), _default_header);
    return (req);
}

std::shared_ptr<ItemsRequest> JellyfinClient::get_items(const std::string &parent_id)
{
    std::ostringstream url;
    gana::Http::UrlParams params = {
        {"ParentId", parent_id},
        {"SortBy", "SortName,ProductionYear"},
        {"SortOrder", "Ascending"},
        {"Limit", "100"}
    };

    url << _url << "/Users/" << _user_id << "/Items";
    std::shared_ptr<ItemsRequest> req = std::make_shared<ItemsRequest>();
    _http.get(req, url.str(), _default_header, params);
    return (req);
}

std::shared_ptr<ItemsRequest> JellyfinClient::get_seasons(const std::string &show_id)
{
    std::ostringstream url;

    url << _url << "/Shows/" << show_id << "/Seasons";
    std::shared_ptr<ItemsRequest> req = std::make_shared<ItemsRequest>();
    _http.get(req, url.str(), _default_header);
    return (req);
}

std::shared_ptr<ItemsRequest> JellyfinClient::get_episodes(const std::string &show_id, const std::string &season_id)
{
    std::ostringstream url;
    gana::Http::UrlParams params = {
        {"seasonid", season_id},
        {"Fields", "Overview"}
    };
    url << _url << "/Shows/" << show_id << "/Episodes";
    std::shared_ptr<ItemsRequest> req = std::make_shared<ItemsRequest>();
    _http.get(req, url.str(), _default_header, params);
    return (req);
}

std::shared_ptr<ItemsRequest> JellyfinClient::get_next_up(const std::string &series_id)
{
    std::ostringstream url;
    gana::Http::UrlParams params = {
        {"UserId", _user_id},
        {"Limit", "16"},
    };
    if (series_id != "")
        params["SeriesId"] = series_id;
    else
        params["DisableFirstEpisode"] = "true";
    url << _url << "/Shows/NextUp";
    std::shared_ptr<ItemsRequest> req = std::make_shared<ItemsRequest>();
    _http.get(req, url.str(), _default_header, params);
    return (req);
}

std::string JellyfinClient::get_img_url(const std::string &img_id, ImageType type) const
{
    std::ostringstream str;
    str << _url << "/Items/" << img_id << "/Images/" << (type == PRIMARY ? "Primary" : "Backdrop");
    return (str.str());
}

std::string JellyfinClient::get_stream_url(const std::string &id) const
{
    std::ostringstream str;

#if SWITCH
    std::size_t pos = _url.find("https");
    if (pos != std::string::npos) {
        std::string tmp = _url;
        tmp.replace(pos, pos + 5, "http");
        str << tmp;
    } else {
        str << _url;
    }
#else
    str << _url;
#endif
    str << "/videos/" << id << "/stream?static=true";
    return (str.str());
}

void JellyfinClient::update_default_header()
{
    std::ostringstream emby_auth;

    emby_auth << "MediaBrowser Client=\"" << CLIENT_NAME << "\", Device=\"" << DEVICE_NAME << "\", Token=" << _token;
    _default_header["X-Emby-Authorization"] = emby_auth.str();
    _default_header["Content-Type"] = "application/json";
}
