
#include "gana/theme/color.hpp"
#include "MediaVignette.hpp"

static const gana::Vector2f SIZE = gana::Vector2f(368, 215);
static const int CORNER_RADIUS = 16;
static const int OUTLINE_CORNER_RADIUS = 18;
static const int PROGRESS_BAR_MARGIN = 16;

MediaVignette::MediaVignette(gana::Http &http, const std::string &url, const Item &item): _item(item)
{
    set_min_size(SIZE);
    set_focusable(true);
    set_margin(16);
    set_color(gana::Color(0, 0, 0, 0));

    _img_background.set_min_size(SIZE);
    _img_background.set_image(http, url, {
        {"fillWidth", std::to_string((int)SIZE.x)},
        {"fillHeight", std::to_string((int)SIZE.y)},
        {"quality", "90"},
    });
    _img_background.set_stretch_mode(gana::Image::StretchMode::KEEP_ASPECT_COVERED);
    _img_background.set_corner_radius(CORNER_RADIUS);
    add_child(&_img_background);

    signal_pressed.connect(*this, &MediaVignette::on_item_pressed);
}

MediaVignette::~MediaVignette()
{}

int MediaVignette::get_outline_corner_radius() const
{
    return (OUTLINE_CORNER_RADIUS);
}

void MediaVignette::on_item_pressed()
{
    on_click.emit(_item);
}
