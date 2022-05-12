
#include "gana/theme/color.hpp"
#include "BigMovieVignette.hpp"

static const gana::Vector2f SIZE = gana::Vector2f(368, 215);
static const int CORNER_RADIUS = 16;
static const int OUTLINE_CORNER_RADIUS = 16;
static const int PROGRESS_BAR_MARGIN = 16;

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
    _lbl_title.set_margin(PROGRESS_BAR_MARGIN, 0, 0, 22);
    _node.add_child(&_lbl_title);

    _pgsb_time_watch.set_anchor(gana::Node::Anchor::BOTTOM_WIDE);
    _pgsb_time_watch.set_color(gana::theme::PRIMARY);
    _pgsb_time_watch.set_progress(item.get_user_data().get_played_percentage());
    _pgsb_time_watch.set_min_size(gana::Vector2f(SIZE.x - PROGRESS_BAR_MARGIN * 2, 10));
    _pgsb_time_watch.set_margin(PROGRESS_BAR_MARGIN, 0, PROGRESS_BAR_MARGIN, 6);
    _node.add_child(&_pgsb_time_watch);

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
