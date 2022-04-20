
#ifndef MPVPLAYER_HPP_
#define MPVPLAYER_HPP_

#include <mpv/client.h>
#include <mpv/render.h>
#include "ui/Node.hpp"

#define DEBUG_MPV 0

namespace gana {

class MPVPlayer: public Node {
    public:
        MPVPlayer();
        ~MPVPlayer();

    protected:
        void process();
        void enter_tree();
    private:
        void set_option_string(const std::string &option, const std::string &value);
#if DEBUG_MPV
        void event();
        static const int OUTPUT_BUFFER_SIZE = 256;
        char output_buffer[OUTPUT_BUFFER_SIZE];
#endif
        mpv_handle *_handle;
        mpv_render_context *_context = nullptr;
        bool _mpv_event;
};

}

#endif /* MPVPLAYER_HPP_ */
