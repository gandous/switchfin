
#ifndef MPVPLAYER_HPP_
#define MPVPLAYER_HPP_

#include <mpv/client.h>
#include <mpv/render.h>
#include "ui/Node.hpp"

namespace gana {

class MPVPlayer: public Node {
    public:
        MPVPlayer();
        ~MPVPlayer();

    protected:
        void process();
        void enter_tree();
    private:
        mpv_handle *_handle;
        mpv_render_context *_context = nullptr;
};

}

#endif /* MPVPLAYER_HPP_ */
