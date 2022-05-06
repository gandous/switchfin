
#include "ItemListRequest.hpp"
#include "Logger.hpp"
#include "json/json.hpp"

ItemListRequest::ItemListRequest()
{}

ItemListRequest::~ItemListRequest()
{}

const Items &ItemListRequest::get_items() const
{
    return (_items);
}

void ItemListRequest::parse()
{
    if (_curl_code != CURLE_OK) {
        _code = ERROR;
    }
    nlohmann::json parse_data = nlohmann::json::parse(_wdata.data);;
    for (auto item: parse_data)
        _items.push_back(item);
    Request::parse();
}
