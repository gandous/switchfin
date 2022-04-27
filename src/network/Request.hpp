
#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include <curl/curl.h>
#include <string>
#include <functional>

class Http;

class Request {
    friend class Http;
    public:
        Request();
        ~Request();

        enum RCode {
            OK = CURLE_OK,
        };
        struct ReadStruct {
            std::string data;
            std::size_t index;
        };
        struct WriteStruct {
            std::string data;
        };
        using callback_func = std::function<void(RCode code, std::string &body)>;
        template<typename T>
        static callback_func mf_callback(T &obj, void(T::*func)(RCode code, std::string &body))
        {
            return ([&obj, func](RCode code, std::string &body){
                (obj.*func)(code, body);
            });
        };

        bool is_completed() const;
        int get_error() const;
        const std::string &get_error_str() const;
        void set_callback(callback_func func);
    protected:
        ReadStruct _rdata;
        WriteStruct _wdata;
        virtual void parse();
        RCode _code;
        callback_func _func;
    private:
        Http *_parent;
        CURL *_handle;
        struct curl_slist *_headers;
        bool _completed;
};

#endif /* REQUEST_HPP_ */