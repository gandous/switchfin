
#ifndef LOGINREQUEST_HPP_
#define LOGINREQUEST_HPP_

#include <string>
#include "json/json.hpp"
#include "Request.hpp"

class LoginRequest: public Request {
    public:
        LoginRequest();
        ~LoginRequest();

        const std::string &get_token() const;
    protected:
        void parse();
    private:
        std::string _token;
        nlohmann::json _json;
};

#endif /* LOGINREQUEST_HPP_ */
