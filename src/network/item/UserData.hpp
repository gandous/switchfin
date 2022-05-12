
#ifndef USERDATA_HPP_
#define USERDATA_HPP_

#include "json/json.hpp"

class UserData {
    public:
        UserData(nlohmann::json &json);
        ~UserData();

        float get_played_percentage() const;
        int get_playback_pos_tick() const;
        int get_play_count() const;
        bool get_is_favorite() const;
    private:
        float _played_percentage;
        int _playback_pos_tick;
        int _play_count;
        bool _is_favorite;
};

#endif /* USERDATA_HPP_ */