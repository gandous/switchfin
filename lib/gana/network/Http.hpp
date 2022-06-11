
#ifndef Http_HPP_
#define Http_HPP_

#include <curl/curl.h>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include "Request.hpp"

namespace gana {

class Http {
    public:
        Http();
        ~Http();

        enum Method {
            POST,
            GET
        };
        using Headers = std::map<std::string, std::string>;
        using UrlParams = std::map<std::string, std::string>;

        int process();
        void request(std::shared_ptr<Request> req, const std::string &url, const std::string &body, Method method, const Headers &headers);
        void post(std::shared_ptr<Request> req, const std::string &url, const std::string &body, const Headers &headers = {}, const UrlParams &url_params = {});
        void get(std::shared_ptr<Request> req, const std::string &url, const Headers &headers = {}, const UrlParams &url_params = {});
        void stop(Request &req);
    private:
        CURL *get_avai_handle();
        void check_response();
        void on_response(CURLMsg *msg);
        std::string format_url_params(const std::string &url, const UrlParams &params);
        CURL *_multi_handle;
        std::list<CURL*> _handles;
        std::vector<std::weak_ptr<Request>> _pending_request;
};

}

#endif /* Http_HPP_ */