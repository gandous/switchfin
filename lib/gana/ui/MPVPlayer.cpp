
#include <SFML/Window/Context.hpp>
// #include <mpv/render.h>
#include <mpv/render_gl.h>
#include <SDL2/SDL_video.h>
#include "App.hpp"
#include "Logger.hpp"
#include "MPVPlayer.hpp"

static void *get_proc_address_mpv(void *unused, const char *name) {
    return ((void*)sf::Context::getFunction(name));
}

static void on_mpv_events(void *ctx)
{
    std::cout << "mpv event" << std::endl;
    mpv_event *mp_event = mpv_wait_event((mpv_handle*)ctx, 0);
    while (mp_event) {
        if (mp_event->event_id == MPV_EVENT_NONE)
            return;
        if (mp_event->event_id == MPV_EVENT_LOG_MESSAGE) {
            mpv_event_log_message *msg = (mpv_event_log_message*)mp_event->data;
            // Print log messages about DR allocations, just to
            // test whether it works. If there is more than 1 of
            // these, it works. (The log message can actually change
            // any time, so it's possible this logging stops working
            // in the future.)
            if (strstr(msg->text, "DR image"))
                printf("log: %s", msg->text);
            continue;
        }
        printf("event: %s\n", mpv_event_name(mp_event->event_id));
        mp_event = mpv_wait_event((mpv_handle*)ctx, 0);
    }
}


namespace gana {

MPVPlayer::MPVPlayer()
{
    _handle = mpv_create();
    if (_handle == nullptr) {
        Logger::error("Failed to init mpv");
        return;
    }
    int error = mpv_initialize(_handle);
    if (error < 0) {
        Logger::error("MPV mpv_initialize failed %s", mpv_error_string(error));
        mpv_destroy(_handle);
        _handle = nullptr;
        return;
    }
    double frame_time = 0;
    mpv_set_option(_handle, "video-timing-offset", MPV_FORMAT_DOUBLE, &frame_time);
    // mpv_request_log_messages(_handle, "debug");
    // mpv_set_option_string(_handle, "msg-level", "all=v");
    // mpv_set_wakeup_callback(_handle, on_mpv_events, _handle);
}

MPVPlayer::~MPVPlayer()
{
    if (_context != nullptr) {
        mpv_render_context_free(_context);
    }
    if (_handle != nullptr) {
        // mpv_destroy(_handle);
        mpv_terminate_destroy(_handle);
    }
}

void MPVPlayer::enter_tree()
{
    set_process(true);
    mpv_opengl_init_params gl_init_params{&get_proc_address_mpv, nullptr, nullptr};
    mpv_render_param params[]{
            {MPV_RENDER_PARAM_API_TYPE,           (void *)MPV_RENDER_API_TYPE_OPENGL},
            {MPV_RENDER_PARAM_OPENGL_INIT_PARAMS, &gl_init_params},
            {MPV_RENDER_PARAM_INVALID,            nullptr}
    };
    int err = mpv_render_context_create(&_context, _handle, params);
    if (err < 0) {
        Logger::error("MPV render_context_create failed %s", mpv_error_string(err));
        return;
    }
    const char *cmd[] = {"loadfile", "http://jellyfin.gama.ovh/videos/044d30e1c62993d8efdac0761a0e1b72/stream?static=true&DeviceId=TW96aWxsYS81LjAgKFgxMTsgRmVkb3JhOyBMaW51eCB4ODZfNjQ7IHJ2Ojk4LjApIEdlY2tvLzIwMTAwMTAxIEZpcmVmb3gvOTguMHwxNjQ5MzQzMjk5NTE3&api_key=c0bda90ebdab46aab26fa61a6a3131f9", NULL};
    err = mpv_command_async(_handle, 0, cmd);
    if (err < 0) {
        Logger::error("MPV mpv_command_async failed %s", mpv_error_string(err));
    }
}

void MPVPlayer::process()
{
    if (mpv_render_context_update(_context) & MPV_RENDER_UPDATE_FRAME) {
        int one{1};
        mpv_opengl_fbo fbo = {
            .fbo = 0,
            .w = (int)_app->get_window().getSize().x,
            .h = (int)_app->get_window().getSize().y,
        };
        mpv_render_param params[] = {
            {MPV_RENDER_PARAM_OPENGL_FBO, &fbo},
            {MPV_RENDER_PARAM_FLIP_Y, &one},
        };
        // on_mpv_events(_handle);
        mpv_render_context_render(_context, params);
    }
}

}
