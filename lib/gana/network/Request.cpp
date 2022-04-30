
#include "Request.hpp"

namespace gana {

Request::Request():
    _parent(nullptr),
    _handle(nullptr),
    _headers(nullptr),
    _completed(false)
{}

Request::~Request()
{}

bool Request::is_completed() const
{
    return (_completed);
}

int Request::get_error() const
{
    return (_code);
}

const std::string &Request::get_error_str() const
{
    return (_error_str);
}

int Request::get_http_code() const
{
    return (_http_code);
}

void Request::set_callback(callback_func func)
{
    _func = func;
}

std::string Request::get_body_as_string() const
{
    return (std::string(&_wdata.data.front(), _wdata.data.size()));
}

const Request::WBody &Request::get_body() const
{
    return (_wdata.data);
}

void Request::parse()
{
    if (_curl_code != CURLE_OK && _error_str == "") {
        _error_str = "Http default error (code: %d)";
        _code = ERROR;
    }
    _func(_code, *this);
}

}
