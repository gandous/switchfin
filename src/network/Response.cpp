
#include "Response.hpp"

Response::Response(int code, const std::string &data): _code(code), _data(data)
{}

Response::~Response()
{}

int Response::get_error() const
{
    return (_code);
}

const std::string &Response::get_error_str() const
{
    switch (_code) {
        default:
            return ("");
    }
}
