
#ifndef Http_HPP_
#define Http_HPP_

#include <curl/curl.h>
#include <list>
#include <string>
#include <functional>
#include <unordered_map>
#include <vector>

class Http {
    public:
        Http();
        ~Http();

        enum Method {
            POST,
            GET
        };
        using callback_func = std::function<void(int code, std::string &body)>;
        struct Request {
            std::string rdata;
            std::size_t rindex;
            std::string wdata;
            CURL* handle;
            callback_func callback;
        };

        int process();
        void request(const std::string &url, const std::string &body, Method method, callback_func callback, std::unordered_map<std::string, std::string> headers);
        void post(const std::string &url, const std::string &body, callback_func callback, std::unordered_map<std::string, std::string> headers = {});
        void get(const std::string &url, const std::string &body, callback_func callback, std::unordered_map<std::string, std::string> headers = {});
    private:
        CURL *get_avai_handle();
        void check_response();
        void on_response(CURLMsg *msg);
        CURL *_multi_handle;
        std::list<CURL*> _handles;
        std::vector<Request> _pending_request;
};

#endif /* Http_HPP_ */