
#include "SmallMovieVignette.hpp"

static const gana::Vector2f SIZE = gana::Vector2f(150, 225);
static const int CORNER_RADIUS = 8;

SmallMovieVignette::SmallMovieVignette(gana::Http &http, const std::string &url, const Item &item): _item(item)
{
    set_min_size(SIZE);
    set_focusable(true);
    set_margin(8);

    _img_background.set_min_size(SIZE);
    _img_background.set_image(http, url, {
        {"fillWidth", std::to_string((int)SIZE.x)},
        {"fillHeight", std::to_string((int)SIZE.y)},
        {"quality", "90"},
    });
    _img_background.set_stretch_mode(gana::Image::StretchMode::KEEP_ASPECT_COVERED);
    _img_background.set_corner_radius(CORNER_RADIUS);
    add_child(&_img_background);
}

SmallMovieVignette::~SmallMovieVignette()
{}

void SmallMovieVignette::process_event(gana::Event &evt)
{
    if (evt.is_touch() && inside_node(gana::Vector2f(evt.touch.x, evt.touch.y))) {
        on_click.emit(_item);
    } else if (has_focus() && evt.accept_pressed()) {
        on_click.emit(_item);
    }
}