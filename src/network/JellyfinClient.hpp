
#ifndef JELLYFINCLIENT_HPP_
#define JELLYFINCLIENT_HPP_

#include <string>
#include <memory>
#include "network/Http.hpp"
#include "network/Request.hpp"
#include "PingRequest.hpp"
#include "LoginRequest.hpp"
#include "item/ItemsRequest.hpp"
#include "item/ItemRequest.hpp"
#include "item/ItemListRequest.hpp"

class JellyfinClient {
    public:
        JellyfinClient(const std::string &url);
        ~JellyfinClient();

        enum ImageType {
            BACKDROP,
            PRIMARY,
        };

        void set_token(const std::string &token);
        void set_user_id(const std::string &id);

        int process();

        const std::string &get_url() const;
        gana::Http &get_http();
        std::shared_ptr<PingRequest> ping();
        std::shared_ptr<LoginRequest> login(const std::string &name, const std::string &password);
        std::shared_ptr<ItemsRequest> get_resume();
        std::shared_ptr<ItemsRequest> get_views();
        std::shared_ptr<ItemListRequest> get_latest(const std::string &parent_id);
        std::shared_ptr<ItemRequest> get_info(const std::string &id);
        std::string get_img_url(const std::string &id, ImageType type = PRIMARY) const;
    private:
        void update_default_header();
        std::string _url;
        gana::Http _http;
        gana::Http::Headers _default_header;
        std::string _token;
        std::string _user_id;
};

#endif /* JELLYFINCLIENT_HPP_ */