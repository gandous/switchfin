
#include "Request.hpp"

Request::Request(): _completed(false)
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
    switch (_code) {
        default:
            return ("");
    }
}

void Request::set_callback(callback_func func)
{
    _func = func;
}

void Request::parse()
{
    _func(_code, _wdata.data);
}
