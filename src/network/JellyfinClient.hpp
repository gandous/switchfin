
#ifndef JELLYFINCLIENT_HPP_
#define JELLYFINCLIENT_HPP_

#include <string>
#include <functional>
#include "Http.hpp"
#include "Response.hpp"
#include "PingResponse.hpp"

class JellyfinClient {
    public:
        JellyfinClient(const std::string &url);
        ~JellyfinClient();

        int process();
        template<typename ...ARGS, typename C>
        std::function<void(ARGS...)> mf_callback(C &obj, void(C::*func)(ARGS...))
        {
            return ([&obj, func](ARGS &...args){
                (obj.*func)(args...);
            });
        }

        void ping(std::function<void(PingResponse &)> callback);
    private:
        std::string _url;
        Http http;
};

#endif /* JELLYFINCLIENT_HPP_ */