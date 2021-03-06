
#include "Logger.hpp"
#include "LoginRequest.hpp"

LoginRequest::LoginRequest()
{}

LoginRequest::~LoginRequest()
{}

const std::string &LoginRequest::get_token() const
{
    return (_token);
}

const std::string &LoginRequest::get_user_id() const
{
    return (_user_id);
}

void LoginRequest::parse()
{
    if (_curl_code == CURLE_OK && _http_code == 200) {
        _json = nlohmann::json::parse(_wdata.data);
        _token = _json["AccessToken"].get<std::string>();
        _user_id = _json["User"]["Id"].get<std::string>();
        _code = OK;
    } else {
        gana::Logger::info("Response %d |%s|", _http_code, get_body_as_string().c_str());
        _code = ERROR;
        _error_str = "Login failed";
    }
    Request::parse();
}