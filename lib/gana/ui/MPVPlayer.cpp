
#include <SFML/Window/Context.hpp>
// #include <mpv/render.h>
#include <mpv/render_gl.h>
#include <SDL2/SDL_video.h>
#include "App.hpp"
#include "MPVPlayer.hpp"

static void *get_proc_address_mpv(void *unused, const char *name) {
    return ((void*)sf::Context::getFunction(name));
}

namespace gana {

MPVPlayer::MPVPlayer()
{
    _handle = mpv_create();
    if (_handle == nullptr) {
        std::cout << "Failed to create mpv handle" << std::endl;
        return;
    }
    if (mpv_initialize(_handle) < 0) {
        std::cout << "mpv init failed" << std::endl;
        return;
    }
}

MPVPlayer::~MPVPlayer()
{}

void MPVPlayer::enter_tree()
{
    std::cout << "start context " << std::endl;
    mpv_opengl_init_params gl_init_params{&get_proc_address_mpv,
                                            nullptr,
                                            nullptr};
    mpv_render_param params[]{
            {MPV_RENDER_PARAM_API_TYPE,           (void *)MPV_RENDER_API_TYPE_OPENGL},
            {MPV_RENDER_PARAM_OPENGL_INIT_PARAMS, &gl_init_params},
            {MPV_RENDER_PARAM_INVALID,            nullptr}
    };
    std::cout << "create context " << std::endl;
    if (mpv_render_context_create(&_context, _handle, params) < 0) {
        // printf("error: mpv_render_context_create: %s\n", mpv_error_string(res));
        std::cout << "error creating context" << std::endl;
    }
    std::cout << "create play " << std::endl;
    // const char *cmd[] = {"loadfile", "https://jellyfin.gama.ovh/videos/78b8477e9704fe1995f3e6341cc603a6/stream\?container\\=mp4\\&DeviceId\\=TW96aWxsYS81LjAgKFgxMTsgRmVkb3JhOyBMaW51eCB4ODZfNjQ7IHJ2Ojk4LjApIEdlY2tvLzIwMTAwMTAxIEZpcmVmb3gvOTguMHwxNjQ5MzQzMjk5NTE3\\&api_key\\=c0bda90ebdab46aab26fa61a6a3131f9", NULL};
    const char *cmd[] = {"loadfile", "http://samples.ffmpeg.org/V-codecs/h264/NeroAVC.mp4", NULL};
    int tmp = 0;
    if ((tmp = mpv_command(_handle, cmd)) < 0) {
        std::cout << "Failed " << mpv_error_string(tmp) << std::endl;
    }
    char *name;
    if ((tmp = mpv_get_property(_handle, "filename", MPV_FORMAT_STRING, &name)) < 0) {
        std::cout << "err get prop"  << mpv_error_string(tmp) << std::endl;
    } else 
        mpv_free(name);
    double res = -1;
    mpv_get_property(_handle, "speed", MPV_FORMAT_DOUBLE, &res);
    if ((tmp = mpv_get_property(_handle, "filename", MPV_FORMAT_STRING, &name)) < 0)
        std::cout << "err get prop"  << mpv_error_string(tmp) << std::endl;
}

void MPVPlayer::draw(NVGcontext *ctx)
{
    int zero{0};
    mpv_opengl_fbo fbo{
        .fbo = 0,
        .w = 1280,
        .h = 720,
    };
    mpv_render_param params[] = {
        // Specify the default framebuffer (0) as target. This will
        // render onto the entire screen. If you want to show the video
        // in a smaller rectangle or apply fancy transformations, you'll
        // need to render into a separate FBO and draw it manually.
        {MPV_RENDER_PARAM_OPENGL_FBO, &fbo},
        // Flip rendering (needed due to flipped GL coordinate system).
        {MPV_RENDER_PARAM_FLIP_Y, &zero},
    };
    long duration = 0;
    if (mpv_get_property(_handle, "time-pos", MPV_FORMAT_INT64, &duration) < 0)
        std::cout << "err get prop" << std::endl;
    std::cout << "render" << duration << " name " << std::endl;
    // See render_gl.h on what OpenGL environment mpv expects, and
    // other API details.
    mpv_render_context_render(_context, params);
}

}
