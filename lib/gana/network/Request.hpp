
#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include <curl/curl.h>
#include <string>
#include <vector>
#include <functional>

namespace gana {

class Http;

class Request {
    friend class Http;
    public:
        Request();
        ~Request();

        enum RCode {
            OK = 0,
            ERROR,
        };
        using WBody = std::vector<unsigned char>;
        struct ReadStruct {
            std::string data;
            std::size_t index;
        };
        struct WriteStruct {
            WBody data;
        };
        using callback_func = std::function<void(RCode code)>;
        template<typename T>
        static callback_func mf_callback(T &obj, void(T::*func)(RCode code))
        {
            return ([&obj, func](RCode code){
                (obj.*func)(code);
            });
        };

        bool is_completed() const;
        int get_error() const;
        const std::string &get_error_str() const;
        int get_http_code() const;
        void set_callback(callback_func func);
        std::string get_body_as_string() const;
        const WBody &get_body() const;
    protected:
        ReadStruct _rdata;
        WriteStruct _wdata;
        virtual void parse();
        RCode _code;
        CURLcode _curl_code;
        long _http_code;
        std::string _error_str;
    private:
        callback_func _func;
        Http *_parent;
        CURL *_handle;
        struct curl_slist *_headers;
        bool _completed;
#if DEBUG_HTTP
        char _err_buffer[CURL_ERROR_SIZE];
        std::string _url;
#endif
};

}

#endif /* REQUEST_HPP_ */