
#include "SeasonVignette.hpp"

static const gana::Vector2f SIZE = gana::Vector2f(162, 243);
static const int OUTLINE_CORNER_RADIUS = 7;

SeasonVignette::SeasonVignette(JellyfinClient &client, const Item &item)
{
    _img.set_image(client.get_http(), client.get_img_url(item.get_id()), {
        {"fillWidth", std::to_string((int)SIZE.x)},
        {"fillHeight", std::to_string((int)SIZE.y)},
        {"quality", "90"},
    });
    _img.set_min_size(SIZE);
    _img.set_corner_radius(4);
    _ctn.add_child(&_img);

    _lbl.set_text(item.get_name());
    _ctn.add_child(&_lbl);

    _ctn.set_space(4);
    add_child(&_ctn);
    set_focusable(true);
    set_margin(15);
}

SeasonVignette::~SeasonVignette()
{}

int SeasonVignette::get_outline_corner_radius() const
{
    return (OUTLINE_CORNER_RADIUS);
}
