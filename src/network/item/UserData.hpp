
#ifndef USERDATA_HPP_
#define USERDATA_HPP_

class UserData {
    public:
        UserData();
        ~UserData();

    private:
        float _played_percentage;
        int _playback_pos_tick;
        int _play_count;
        bool _is_favorite;
};

#endif /* USERDATA_HPP_ */