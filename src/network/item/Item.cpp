
#include "Item.hpp"

static std::string get_string(nlohmann::json &json, const std::string &key)
{
    return (json[key].is_string() ? json[key].get<std::string>() : "");
}

Item::Item(nlohmann::json &json):
    _name(json["Name"].get<std::string>()),
    _original_title(json["Name"].get<std::string>()),
    _server_id(json["ServerId"].get<std::string>()),
    _id(json["Id"].get<std::string>()),
    _etag(get_string(json, "Etag")),
    _path(get_string(json, "Path")),
    _official_rating(get_string(json, "OfficialRating")),
    _overview(get_string(json, "Overview")),
    _community_rating(json["CommunityRating"].is_number_float() ? json["CommunityRating"].get<float>() : 0),
    _runtime_tick(json["ProductionYear"].is_number_integer() ? json["RunTimeTicks"].get<int>() : 0),
    _prod_year(json["ProductionYear"].is_number_integer() ? json["ProductionYear"].get<int>() : 0),
    _is_hd(json["IsHD"].is_boolean() ? json["IsHD"].get<bool>() : false),
    _is_folder(json["IsFolder"].is_boolean() ? json["IsFolder"].get<bool>() : false),
    _parent_id(get_string(json, "ParentId")),
    _type(parse_type(get_string(json, "Type")))
{
    if (json["Genres"].is_array())
        _genres = json["Genres"].get<std::vector<std::string>>();
    if (json["Taglines"].is_array())
        _taglines = json["Taglines"].get<std::vector<std::string>>();
}

Item::~Item()
{}

const std::string &Item::get_name() const
{
    return (_name);
}

const std::string &Item::get_original_title() const
{
    return (_original_title);
}

const std::string &Item::get_server_id() const
{
    return (_server_id);
}

const std::string &Item::get_id() const
{
    return (_id);
}

const std::string &Item::get_etag() const
{
    return (_etag);
}

const std::string &Item::get_path() const
{
    return (_path);
}

const std::string &Item::get_official_rating() const
{
    return (_official_rating);
}

const std::string &Item::get_overview() const
{
    return (_overview);
}

const std::vector<std::string> &Item::get_taglines() const
{
    return (_taglines);
}

const std::vector<std::string> &Item::get_genres() const
{
    return (_genres);
}

float Item::get_community_rating() const
{
    return (_community_rating);
}

int Item::get_runtime_tick() const
{
    return (_runtime_tick);
}

int Item::get_prod_year() const
{
    return (_prod_year);
}

bool Item::get_is_hd() const
{
    return (_is_hd);
}

bool Item::get_is_folder() const
{
    return (_is_folder);
}

const std::string &Item::get_parent_id() const
{
    return (_parent_id);
}

Item::Type Item::get_type() const
{
    return (_type);
}

Item::Type Item::parse_type(const std::string &type)
{
    if (type == "Movie")
        return (Type::MOVIE);
    else if (type == "Serie")
        return (Type::SERIE);
    else
        return (Type::UNKNOW);
}
