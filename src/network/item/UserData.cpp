
#include "UserData.hpp"

UserData::UserData(nlohmann::json &json):
    _played_percentage(json["PlayedPercentage"].is_number_float() ? json["PlayedPercentage"].get<float>() : 0.f),
    _playback_pos_tick(json["PlacbackPositionTicks"].is_number_integer() ? json["PlacbackPositionTicks"].get<int>() : 0),
    _play_count(json["PlayCount"].is_number_integer() ? json["PlayCount"].get<int>() : 0),
    _is_favorite(json["IsFavorite"].is_boolean() ? json["IsFavorite"].get<bool>() : false)
{}

UserData::~UserData()
{}

float UserData::get_played_percentage() const
{
    return (_played_percentage);
}

int UserData::get_playback_pos_tick() const
{
    return (_playback_pos_tick);
}

int UserData::get_play_count() const
{
    return (_play_count);
}

bool UserData::get_is_favorite() const
{
    return (_is_favorite);
}

