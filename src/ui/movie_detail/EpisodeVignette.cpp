
#include "network/item/duration.hpp"
#include "gana/theme/color.hpp"
#include "EpisodeVignette.hpp"

static const gana::Vector2f SIZE = gana::Vector2f(300, 168);

EpisodeVignette::EpisodeVignette(JellyfinClient &client, const Item &item): _item(item)
{
    set_color(gana::Color(21, 21, 21, 211));
    set_corner_radius(7);

    _img.set_image(client.get_http(), client.get_img_url(item.get_id()), {
        {"fillWidth", std::to_string((int)SIZE.x)},
        {"fillHeight", std::to_string((int)SIZE.y)},
        {"quality", "90"},
    });
    _img.set_min_size(SIZE);
    _img.set_corner_radius(7);
    _img.set_stretch_mode(gana::Image::StretchMode::KEEP_ASPECT_COVERED);
    _ctn.add_child(&_img);

    _lbl_title.set_text(item.get_name());
    _lbl_title.set_max_length(60);
    _lbl_title.set_font_size(24);
    _ctn_text.add_child(&_lbl_title);

    _lbl_duration.set_text(tick_to_duration(item.get_runtime_tick()));
    _lbl_duration.set_color(gana::theme::TEXT_COLOR_SECONDARY);
    _lbl_duration.set_font_size(20);
    _ctn_text.add_child(&_lbl_duration);

    _lbl_overview.set_text(item.get_overview());
    _lbl_overview.set_font_size(14);
    _lbl_overview.set_color(gana::theme::TEXT_COLOR_SECONDARY);
    _lbl_overview.set_hsizing(gana::Node::Sizing::FILL);
    _ctn_text.add_child(&_lbl_overview);

    _ctn_text.set_expand();
    _ctn.add_child(&_ctn_text);

    _ctn_play_button.set_vsizing(gana::Node::Sizing::SHRINK_CENTER);
    _ctn.add_child(&_ctn_play_button);

    _ctn.set_space(4);
    add_child(&_ctn);
    set_focusable(true);
    set_content_margin(8);
}

EpisodeVignette::~EpisodeVignette()
{}

// int EpisodeVignette::get_outline_corner_radius() const
// {
//     return (OUTLINE_CORNER_RADIUS);
// }

void EpisodeVignette::process_event(gana::Event &evt)
{
    if (evt.is_touch() && inside_node(gana::Vector2f(evt.touch.x, evt.touch.y))) {
        signal_pressed.emit(_item);
    } else if (has_focus() && evt.accept_pressed()) {
        signal_pressed.emit(_item);
    }
}

