
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

        template<typename ...ARGS, typename C>
        std::function<void(ARGS...)> mf_callback(C &obj, void(C::*func)(ARGS...))
        {
            return ([&obj, func](ARGS &...args){
                (obj.*func)(args...);
            });
        };
        struct ReadStruct {
            std::string data;
            std::size_t index;
        };
        struct WriteStruct {
            std::string data;
        };
        using callback_func = std::function<void(int code, std::string &body)>;

        bool is_completed() const;
        int get_error() const;
        const std::string &get_error_str() const;
        void set_callback(callback_func func);
    protected:
        ReadStruct _rdata;
        WriteStruct _wdata;
        void parse();
        int _code;
        callback_func _func;
    private:
        Http *_parent;
        CURL *_handle;
        struct curl_slist *_headers;
        bool _completed;
};

#endif /* REQUEST_HPP_ */