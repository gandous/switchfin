
#ifndef Http_HPP_
#define Http_HPP_

#include <curl/curl.h>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Request.hpp"

class Http {
    public:
        Http();
        ~Http();

        enum Method {
            POST,
            GET
        };
        using Headers = std::unordered_map<std::string, std::string>;

        int process();
        void request(std::shared_ptr<Request> req, const std::string &url, const std::string &body, Method method, const std::unordered_map<std::string, std::string> &headers);
        void post(std::shared_ptr<Request> req, const std::string &url, const std::string &body, const std::unordered_map<std::string, std::string> &headers = {});
        void get(std::shared_ptr<Request> req, const std::string &url, const std::unordered_map<std::string, std::string> &headers = {});
    private:
        CURL *get_avai_handle();
        void check_response();
        void on_response(CURLMsg *msg);
        CURL *_multi_handle;
        std::list<CURL*> _handles;
        std::vector<std::weak_ptr<Request>> _pending_request;
};

#endif /* Http_HPP_ */