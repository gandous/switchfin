
#include "ItemsRequest.hpp"
#include "Logger.hpp"
#include "json/json.hpp"

ItemsRequest::ItemsRequest()
{}

ItemsRequest::~ItemsRequest()
{}

const Items &ItemsRequest::get_items() const
{
    return (_items);
}

void ItemsRequest::parse()
{
    if (_curl_code != CURLE_OK) {
        _code = ERROR;
    }
    nlohmann::json parse_data = nlohmann::json::parse(_wdata.data);
    for (auto item: parse_data["Items"])
        _items.push_back(item);
    Request::parse();
}
