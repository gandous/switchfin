
#include "ItemRequest.hpp"
#include "Logger.hpp"
#include "json/json.hpp"

ItemRequest::ItemRequest()
{}

ItemRequest::~ItemRequest()
{}

const Item &ItemRequest::get_item() const
{
    return (*_item.get());
}

void ItemRequest::parse()
{
    if (_curl_code != CURLE_OK) {
        _code = ERROR;
    }
    nlohmann::json parse_data = nlohmann::json::parse(_wdata.data);
    _item = std::make_unique<Item>(parse_data);
    Request::parse();
}
