
#include "BigMovieVignette.hpp"

static const gana::Vector2f SIZE = gana::Vector2f(368, 215);

BigMovieVignette::BigMovieVignette(gana::Http &http, const std::string &url)
{
    set_min_size(SIZE);

    _img_background.set_min_size(SIZE);
    _img_background.set_image(http, url, {
        {"fillHeight", std::to_string((int)SIZE.x)},
        {"fillWidth", std::to_string((int)SIZE.y)},
        {"quality", "90"},
    });
    _img_background.set_stretch_mode(gana::Image::StretchMode::KEEP_ASPECT_COVERED);
    add_child(&_img_background);
}

BigMovieVignette::~BigMovieVignette()
{}
