
#ifndef LOGINREQUEST_HPP_
#define LOGINREQUEST_HPP_

#include <string>
#include "json/json.hpp"
#include "network/Request.hpp"

class LoginRequest: public gana::Request {
    public:
        LoginRequest();
        ~LoginRequest();

        const std::string &get_token() const;
        const std::string &get_user_id() const;
    protected:
        void parse();
    private:
        std::string _token;
        std::string _user_id;
        nlohmann::json _json;
};

#endif /* LOGINREQUEST_HPP_ */
