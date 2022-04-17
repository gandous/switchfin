
#include "PingResponse.hpp"

PingResponse::PingResponse(int code, const std::string &data): Response(code, data)
{}

PingResponse::~PingResponse()
{}
