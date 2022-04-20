
#include "Switchfin.hpp"

int main()
{
    Switchfin app;

    app.run();
    return (0);
}


// #include <stddef.h>
// #include <stdio.h>
// #include <stdlib.h>

// #include <unistd.h>
// #include <mpv/client.h>
// #include <mpv/render_gl.h>

// #include <iostream>
// #include <cstring>
// #include <SFML/Window.hpp>

// static void die(const char *msg)
// {
//     printf("%s\n", msg);
// }

// static void *get_proc_address_mpv(void *fn_ctx, const char *name)
// {
//     return (void*)sf::Context::getFunction(name);
// }

// static bool mpv_events = false;
// static void on_mpv_events(void *ctx)
// {
//     mpv_events = true;
// }

// static bool mpv_render_event = false;
// static void on_mpv_render_update(void *ctx)
// {
//     mpv_render_event = true;
// }


// static void mon_event(void *ctx)
// {
//     // std::cout << "mpv event" << std::endl;
//     mpv_event *mp_event = mpv_wait_event((mpv_handle*)ctx, 0);
//     while (mp_event) {
//         if (mp_event->event_id == MPV_EVENT_NONE)
//             return;
//         if (mp_event->event_id == MPV_EVENT_LOG_MESSAGE) {
//             mpv_event_log_message *msg = (mpv_event_log_message*)mp_event->data;
//             // Print log messages about DR allocations, just to
//             // test whether it works. If there is more than 1 of
//             // these, it works. (The log message can actually change
//             // any time, so it's possible this logging stops working
//             // in the future.)
//             // if (strstr(msg->text, "DR image"))
//                 printf("log: %s", msg->text);
//             continue;
//         }
//         printf("event: %s\n", mpv_event_name(mp_event->event_id));
//         mp_event = mpv_wait_event((mpv_handle*)ctx, 0);
//     }
// }

// int main(int argc, char *argv[])
// {
//     // if (argc != 2)
//     //     die("pass a single media file as argument");
//     socketInitializeDefault();
//     nxlinkStdio();
//     printf("OK1\n");
//     mpv_handle *mpv = mpv_create();
//     if (!mpv)
//         die("context init failed");

//     printf("OK1\n");
//     // Some minor options can only be set before mpv_initialize().
//     if (mpv_initialize(mpv) < 0)
//         die("mpv init failed");
//     mpv_request_log_messages(mpv, "debug");

//     printf("OK2\n");
//     sf::Window window(sf::VideoMode::getDesktopMode(), "slt");
//     window.setFramerateLimit(60);

//     mpv_opengl_init_params gl_init_params{&get_proc_address_mpv, nullptr, nullptr};
//     int one = 2;
//     mpv_render_param params[] = {
//         {MPV_RENDER_PARAM_API_TYPE, (void*)MPV_RENDER_API_TYPE_OPENGL},
//         {MPV_RENDER_PARAM_OPENGL_INIT_PARAMS, &gl_init_params},
//         {MPV_RENDER_PARAM_ADVANCED_CONTROL, &one},
//         {(mpv_render_param_type)0}
//     };


//     mpv_set_option_string(mpv, "vd-lavc-threads", "4");
//     // TODO: test this
//     mpv_set_option_string(mpv, "fbo-format", "rgba8");
//     mpv_set_option_string(mpv, "opengl-pbo", "yes");

//     printf("OK3\n");
//     // This makes mpv use the currently set GL context. It will use the callback
//     // (passed via params) to resolve GL builtin functions, as well as extensions.
//     mpv_render_context *mpv_gl;
//     if (mpv_render_context_create(&mpv_gl, mpv, params) < 0)
//         die("failed to initialize mpv GL context");

//     printf("OK4\n");

//     mpv_set_wakeup_callback(mpv, on_mpv_events, NULL);
//     mpv_render_context_set_update_callback(mpv_gl, on_mpv_render_update, NULL);

//     // Play this file.
//     // const char *cmd[] = {"loadfile", "http://samples.ffmpeg.org/V-codecs/h264/NeroAVC.mp4", NULL};
//     // const char *cmd[] = {"loadfile", "http://jellyfin.gama.ovh/videos/044d30e1c62993d8efdac0761a0e1b72/stream?static=true&DeviceId=TW96aWxsYS81LjAgKFgxMTsgRmVkb3JhOyBMaW51eCB4ODZfNjQ7IHJ2Ojk4LjApIEdlY2tvLzIwMTAwMTAxIEZpcmVmb3gvOTguMHwxNjQ5MzQzMjk5NTE3&api_key=c0bda90ebdab46aab26fa61a6a3131f9", NULL};
//     const char *cmd[] = {"loadfile", "http://5.135.166.198:8096/videos/044d30e1c62993d8efdac0761a0e1b72/stream?static=true&DeviceId=TW96aWxsYS81LjAgKFgxMTsgRmVkb3JhOyBMaW51eCB4ODZfNjQ7IHJ2Ojk4LjApIEdlY2tvLzIwMTAwMTAxIEZpcmVmb3gvOTguMHwxNjQ5MzQzMjk5NTE3&api_key=c0bda90ebdab46aab26fa61a6a3131f9", NULL};
//     mpv_command_async(mpv, 0, cmd);
//     printf("OK\n");

//     bool draw = false;
//     while (window.isOpen()) {
//         sf::Event evt;
//         while (window.pollEvent(evt)) {
//             if (evt.type == sf::Event::Closed)
//                 window.close();
//         }
//         if (mpv_render_event) {
//             uint64_t flags = mpv_render_context_update(mpv_gl);
//             if (flags & MPV_RENDER_UPDATE_FRAME)
//                 draw = true;
//             mpv_render_event = false;
//         }
//         // Happens when at least 1 new event is in the mpv event queue.
//         if (mpv_events) {
//             // Handle all remaining mpv events.
//             while (1) {
//                 mpv_event *mp_event = (mpv_event*)mpv_wait_event(mpv, 0);
//                 if (mp_event->event_id == MPV_EVENT_NONE)
//                     break;
//                 if (mp_event->event_id == MPV_EVENT_LOG_MESSAGE) {
//                     mpv_event_log_message *msg = (mpv_event_log_message*)mp_event->data;
//                     // Print log messages about DR allocations, just to
//                     // test whether it works. If there is more than 1 of
//                     // these, it works. (The log message can actually change
//                     // any time, so it's possible this logging stops working
//                     // in the future.)
//                     // if (strstr(msg->text, "DR image"))
//                         printf("log: %s", msg->text);
//                     continue;
//                 }
//                 printf("event: %s\n", mpv_event_name(mp_event->event_id));
//             }
//             mpv_events = false;
//         }
//         if (draw) {
//             mpv_opengl_fbo fbo = {
//                 .fbo = 0,
//                 .w = (int)window.getSize().x,
//                 .h = (int)window.getSize().y,
//             };
//             mpv_render_param params[] = {
//                 {MPV_RENDER_PARAM_OPENGL_FBO, &fbo},
//                 // Flip rendering (needed due to flipped GL coordinate system).
//                 {MPV_RENDER_PARAM_FLIP_Y, &one},
//                 {(mpv_render_param_type)0}
//             };
//             // See render_gl.h on what OpenGL environment mpv expects, and
//             // other API details.
//             mpv_render_context_render(mpv_gl, params);
//             draw = false;
//         }
//         window.display();

//     }
//     mpv_render_context_free(mpv_gl);

//     mpv_detach_destroy(mpv);

//     printf("properly terminated\n");
//     return 0;
// }