
#include "PingRequest.hpp"

PingRequest::PingRequest()
{}

PingRequest::~PingRequest()
{}

void PingRequest::parse()
{
    if (_curl_code != CURLE_OK) {
        _error_str = "Failed to connect.";
        _code = ERROR;
    } else if (_wdata.data != "\"Jellyfin Server\"") {
        _error_str = "Url is not a Jellyfin server.";
        _code = ERROR;
    } else {
        _code = OK;
    }
    Request::parse();
}
