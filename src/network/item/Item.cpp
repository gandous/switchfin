
#include "Item.hpp"

Item::Item(nlohmann::json &json)
{
    _name = json["Name"].get<std::string>();
}

Item::~Item()
{}

const std::string &Item::get_name() const
{
    return (_name);
}
