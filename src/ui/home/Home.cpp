
#include "ui/ScrollView.hpp"
#include "ui/ColorRect.hpp"
#include "LatestView.hpp"
#include "App.hpp"
#include "ui/movie_detail/MovieDetail.hpp"
#include "Home.hpp"

Home::Home(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client): _nav(nav), _jclient(client)
{
    set_color(gana::Color(19, 19, 19));
    set_min_size(gana::Vector2f(500, 500));
    set_anchor(gana::Node::Anchor::FULL_RECT);
    _rresume = _jclient->get_resume();
    _rresume->set_callback(gana::Request::mf_callback(*this, &Home::on_resume_receive));
    _rviews = _jclient->get_views();
    _rviews->set_callback(gana::Request::mf_callback(*this, &Home::on_views_receive));

    gana::ScrollView *vscroll = _ctn_main.make_managed<gana::ScrollView>();
    vscroll->set_anchor(gana::Node::FULL_RECT);
    vscroll->set_scroll_direction(gana::ScrollView::Y);
    add_child(vscroll);

    _ctn_main.set_hsizing(gana::Node::Sizing::FILL);
    _ctn_main.set_expand();
    vscroll->add_child(&_ctn_main);

    _lbl_continue_watching.set_text("Continue watching");
    _lbl_continue_watching.set_font_size(40);
    _ctn_main.add_child(&_lbl_continue_watching);

    gana::ScrollView *scroll = _ctn_main.make_managed<gana::ScrollView>();
    scroll->set_hsizing(gana::Node::Sizing::FILL);
    scroll->set_scroll_direction(gana::ScrollView::X);
    _ctn_main.add_child(scroll);

    _lbl_next_up.set_text("Next up");
    _lbl_next_up.set_font_size(40);
    _ctn_main.add_child(&_lbl_next_up);

    _ctn_resume_movie.set_expand();
    scroll->add_child(&_ctn_resume_movie);
}

Home::~Home()
{}

void Home::enter_tree()
{
    set_process(true);
    _app->set_focused_node(&_lbl_continue_watching);
}

void Home::process()
{
    _jclient->process();
}

void Home::on_resume_receive(gana::Request::RCode code, gana::Request &req)
{
    if (code != gana::Request::OK) {
        gana::Logger::error("%s", _rresume->get_error_str().c_str());
        return;
    }
    for (auto &item: _rresume->get_items()) {
        BigMovieVignette *vign = _ctn_resume_movie.make_managed<BigMovieVignette>(_jclient->get_http(), _jclient->get_img_url(item.get_id(), JellyfinClient::BACKDROP), item);
        vign->set_vsizing(gana::Node::Sizing::SHRINK_CENTER);
        vign->on_click.connect(*this, &Home::on_item_click);
        gana::Logger::info("Name: %s", item.get_name().c_str());
        _ctn_resume_movie.add_child(vign);
    }
    _app->set_focused_node(&_ctn_resume_movie);
}

void Home::on_views_receive(gana::Request::RCode code, gana::Request &req)
{
    if (code != gana::Request::OK) {
        gana::Logger::error("%s", req.get_error_str().c_str());
        return;
    }
    for (auto &item: _rviews->get_items()) {
        gana::Logger::info("View: %s", item.get_name().c_str());
        gana::Label *lbl = make_managed<gana::Label>();
        lbl->set_text("Latest " + item.get_name());
        lbl->set_font_size(40);
        _ctn_main.add_child(lbl);
        LatestView *view = make_managed<LatestView>(*_jclient.get(), item.get_id());
        _ctn_main.add_child(view);
    }
}

void Home::on_item_click(const Item &item)
{
    gana::Logger::info("Item click %s", item.get_name().c_str());
    _nav.navigate_down<MovieDetail>(_jclient, item);
}
