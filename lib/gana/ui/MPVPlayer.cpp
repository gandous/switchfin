
#include <SFML/Window/Context.hpp>
// #include <mpv/render.h>
#include <mpv/render_gl.h>
#include <cstring>
#include "App.hpp"
#include "Logger.hpp"
#include "MPVPlayer.hpp"

static void *get_proc_address_mpv(void *unused, const char *name) {
    return ((void*)sf::Context::getFunction(name));
}

static void on_mpv_events(void *ctx)
{
    bool *evt = (bool*)ctx;
    *evt = true;
}


namespace gana {

MPVPlayer::MPVPlayer(): _mpv_event(false)
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
    mpv_request_log_messages(_handle, "debug");
    set_option_string("vd-lavc-threads", "4");
    set_option_string("fbo-format", "rgba8");
    set_option_string("opengl-pbo", "yes");
    // mpv_set_option_string(_handle, "msg-level", "all=v");
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
    mpv_set_wakeup_callback(_handle, on_mpv_events, &_mpv_event);
}

void MPVPlayer::process()
{
#if DEBUG_MPV
    event();
#endif
    mpv_render_context_update(_context);
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
    mpv_render_context_render(_context, params);
}

void MPVPlayer::set_option_string(const std::string &option, const std::string &value)
{
    int ret = mpv_set_option_string(_handle, option.c_str(), value.c_str());
    if (ret < 0)
        Logger::error("MPV Failed to set option %s with value: %s", option, value);
}

#if DEBUG_MPV
void MPVPlayer::event()
{
    if (_mpv_event) {
        while (1) {
            mpv_event *mp_event = mpv_wait_event(_handle, 0);
            if (mp_event->event_id == MPV_EVENT_NONE)
                break;
            if (mp_event->event_id == MPV_EVENT_LOG_MESSAGE) {
                mpv_event_log_message *msg = (mpv_event_log_message*)mp_event->data;
                std::strncpy(output_buffer, msg->text, OUTPUT_BUFFER_SIZE);
                output_buffer[OUTPUT_BUFFER_SIZE - 1] = '\0';
                output_buffer[std::strlen(output_buffer) - 1] = '\0';
                Logger::info("MPV: %s %s", msg->prefix, output_buffer);
                continue;
            }
            Logger::info("MPV event: %s", mpv_event_name(mp_event->event_id));
        }
        _mpv_event = false;
    }
}
#endif

}
