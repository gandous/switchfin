
#include "Item.hpp"

Item::Item(nlohmann::json &json)
{
    _name = json["Name"].get<std::string>();
    _id = json["Id"].get<std::string>();
}

Item::~Item()
{}

const std::string &Item::get_name() const
{
    return (_name);
}

const std::string &Item::get_id() const
{
    return (_id);
}
