
#include "LoginRequest.hpp"

LoginRequest::LoginRequest()
{}

LoginRequest::~LoginRequest()
{}

const std::string &LoginRequest::get_token() const
{
    return (_token);
}

void LoginRequest::parse()
{
    if (_code != Request::OK)
        return;
    _json = nlohmann::json::parse(_wdata.data);
    _token = _json["AccessToken"].get<std::string>();
    Request::parse();
}