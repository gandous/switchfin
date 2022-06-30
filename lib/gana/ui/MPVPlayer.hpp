
#ifndef MPVPLAYER_HPP_
#define MPVPLAYER_HPP_

#include <mpv/client.h>
#include <mpv/render.h>
#include "ui/Node.hpp"
#include "type/Signal.hpp"

#define DEBUG_MPV 0

namespace gana {

class MPVPlayer: public Node {
    public:
        MPVPlayer();
        ~MPVPlayer();

        enum TrackType {
            AUDIO,
            VIDEO,
            SUB,
        };
        struct Track {
            TrackType type;
            int64_t id;
            std::string title;
            std::string lang;
            bool selected;
        };

        void set_source(const std::string &src);
        bool is_seeking();
        bool is_core_idle();
        int64_t get_time_pos();
        void set_time_pos(int64_t pos);
        int64_t get_duration();
        void set_pause(bool pause = true);
        bool is_pause();
        int64_t get_track_count();
        Track get_track(int id);

        Signal<> signal_file_loaded;
    protected:
        void process();
        void enter_tree();
    private:
        void set_option_string(const std::string &option, const std::string &value);
        void event();
        std::string get_track_str_prop(int id, const std::string &prop);
        int64_t get_track_int_prop(int id, const std::string &prop);
#if DEBUG_MPV
        static const int OUTPUT_BUFFER_SIZE = 256;
        char output_buffer[OUTPUT_BUFFER_SIZE];
#endif
        mpv_handle *_handle;
        mpv_render_context *_context = nullptr;
        bool _mpv_event;
        std::string _src;
};

}

#endif /* MPVPLAYER_HPP_ */
