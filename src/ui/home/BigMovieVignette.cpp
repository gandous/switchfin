
#include "BigMovieVignette.hpp"

static const gana::Vector2f SIZE = gana::Vector2f(368, 215);
static const int CORNER_RADIUS = 16;
static const int OUTLINE_CORNER_RADIUS = 16;

BigMovieVignette::BigMovieVignette(gana::Http &http, const std::string &url, const Item &item): _item(item)
{
    set_min_size(SIZE);
    set_margin(16);

    _img_background.set_min_size(SIZE);
    _img_background.set_image(http, url, {
        {"fillWidth", std::to_string((int)SIZE.x)},
        {"fillHeight", std::to_string((int)SIZE.y)},
        {"quality", "90"},
    });
    _img_background.set_stretch_mode(gana::Image::StretchMode::KEEP_ASPECT_COVERED);
    _img_background.set_corner_radius(CORNER_RADIUS);
    add_child(&_img_background);

    _gdt_background.set_icolor(gana::Color(0, 0, 0, 0));
    _gdt_background.set_ocolor(gana::Color(0, 0, 0));
    _gdt_background.set_corner_radius(CORNER_RADIUS);
    _gdt_background.set_anchor(gana::Node::FULL_RECT);
    add_child(&_gdt_background);

    _lbl_title.set_text(item.get_name());
    _lbl_title.set_anchor(gana::Node::Anchor::BOTTOM_LEFT);
    _lbl_title.set_text_valign(gana::Label::BOTTOM);
    _lbl_title.set_max_length(35);
    _node.add_child(&_lbl_title);

    _node.set_anchor(gana::Node::Anchor::FULL_RECT);
    add_child(&_node);
}

BigMovieVignette::~BigMovieVignette()
{}

int BigMovieVignette::get_outline_corner_radius() const
{
    return (OUTLINE_CORNER_RADIUS);
}

void BigMovieVignette::process_event(gana::Event &evt)
{
    if (evt.is_touch() && inside_node(gana::Vector2f(evt.touch.x, evt.touch.y))) {
        on_click.emit(_item);
    } else if (has_focus() && evt.accept_pressed()) {
        on_click.emit(_item);
    }
}
