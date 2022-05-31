
#include <SFML/Window/Context.hpp>
// #include <mpv/render.h>
#include <mpv/render_gl.h>
#include <cstring>
#include "App.hpp"
#include "Logger.hpp"
#include "MPVPlayer.hpp"

static void *get_proc_address_mpv(void *unused, const char *name) {
    (void)unused;
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

void MPVPlayer::set_source(const std::string &src)
{
    _src = src;
}

bool MPVPlayer::is_seeking()
{
    int64_t seeking;
    mpv_get_property(_handle, "seeking", MPV_FORMAT_INT64, &seeking);
    return (seeking == 1);
}

bool MPVPlayer::is_core_idle()
{
    int64_t core_idle;
    mpv_get_property(_handle, "core-idle", MPV_FORMAT_INT64, &core_idle);
    return (core_idle == 1);
}

int64_t MPVPlayer::get_time_pos()
{
    int64_t data;
    mpv_get_property(_handle, "time-pos", MPV_FORMAT_INT64, &data);
    return (data);
}

void MPVPlayer::set_time_pos(int64_t pos)
{
    mpv_set_property(_handle, "time-pos", MPV_FORMAT_INT64, &pos);
}

int64_t MPVPlayer::get_duration()
{
    int64_t data;
    mpv_get_property(_handle, "duration", MPV_FORMAT_INT64, &data);
    return (data);
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
    const char *cmd[] = {"loadfile", _src.c_str(), NULL};
    err = mpv_command_async(_handle, 0, cmd);
    if (err < 0) {
        Logger::error("MPV mpv_command_async failed %s", mpv_error_string(err));
    }
    mpv_set_wakeup_callback(_handle, on_mpv_events, &_mpv_event);
}

void MPVPlayer::process()
{
    event();
    // We don't wait for the MPV_RENDER_UPDATE_FRAME signal to draw
    // Because otherwise when swapping back and front buffer we will redraw the previous frame
    mpv_render_context_update(_context);
    int one{1};
    mpv_opengl_fbo fbo = {
        .fbo = 0,
        .w = (int)_app->get_window().getSize().x,
        .h = (int)_app->get_window().getSize().y,
        .internal_format = 0,
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

void MPVPlayer::event()
{
    if (!_mpv_event)
        return;
    while (1) {
        mpv_event *mp_event = mpv_wait_event(_handle, 0);
        if (mp_event->event_id == MPV_EVENT_NONE) {
            break;
        } else if (mp_event->event_id == MPV_EVENT_LOG_MESSAGE) {
#if DEBUG_MPV
            mpv_event_log_message *msg = (mpv_event_log_message*)mp_event->data;
            std::strncpy(output_buffer, msg->text, OUTPUT_BUFFER_SIZE);
            output_buffer[OUTPUT_BUFFER_SIZE - 1] = '\0';
            output_buffer[std::strlen(output_buffer) - 1] = '\0';
            Logger::info("MPV: %s %s", msg->prefix, output_buffer);
#endif
        } else if (mp_event->event_id == MPV_EVENT_END_FILE) {
            mpv_event_end_file *data = (mpv_event_end_file*)mp_event->data;
            if (data->reason == MPV_END_FILE_REASON_ERROR) {
                Logger::error("MPV %s", mpv_error_string(data->error));
            } else {
                Logger::info("MPV event: END OF FILE");
            }
        } else {
            Logger::info("MPV event: %s", mpv_event_name(mp_event->event_id));
            if (mp_event->event_id == MPV_EVENT_FILE_LOADED)
                signal_file_loaded.emit();
        }
    }
    _mpv_event = false;
}

}
