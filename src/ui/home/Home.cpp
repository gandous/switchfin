
#include "ui/ColorRect.hpp"
#include "LatestView.hpp"
#include "App.hpp"
#include "ui/movie_detail/MovieDetail.hpp"
#include "ui/movie_detail/SerieDetail.hpp"
#include "ui/movie_detail/EpisodeDetail.hpp"
#include "Home.hpp"


Home::Home(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client): _nav(nav), _jclient(client)
{
    set_color(gana::Color(19, 19, 19));
    set_min_size(gana::Vector2f(500, 500));
    set_anchor(gana::Node::Anchor::FULL_RECT);
    _rresume = _jclient->get_resume();
    _rresume->set_callback(gana::Request::mf_callback(*this, &Home::on_resume_receive));
    _rnext_up = _jclient->get_next_up();
    _rnext_up->set_callback(gana::Request::mf_callback(*this, &Home::on_next_up_receive));
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

    _scr_resume.set_hsizing(gana::Node::Sizing::FILL);
    _scr_resume.set_scroll_direction(gana::ScrollView::X);
    _ctn_main.add_child(&_scr_resume);

    _lbl_next_up.set_text("Next up");
    _lbl_next_up.set_font_size(40);
    _ctn_main.add_child(&_lbl_next_up);

    gana::ScrollView *scroll_next_up = _ctn_main.make_managed<gana::ScrollView>();
    scroll_next_up->set_hsizing(gana::Node::Sizing::FILL);
    scroll_next_up->set_scroll_direction(gana::ScrollView::X);
    _ctn_main.add_child(scroll_next_up);

    _ctn_next_up.set_expand();
    scroll_next_up->add_child(&_ctn_next_up);

    _ctn_resume_movie.set_expand();
    _scr_resume.add_child(&_ctn_resume_movie);
}

Home::~Home()
{}

void Home::enter_tree()
{
    set_process(true);
    _app->set_focused_node(&_ctn_resume_movie);
}

void Home::process()
{
    _jclient->process();
}

void Home::on_resume_receive(gana::Request::RCode code)
{
    if (code != gana::Request::OK) {
        gana::Logger::error("%s", _rresume->get_error_str().c_str());
        return;
    }
    for (auto &item: _rresume->get_items()) {
        std::string url = _jclient->get_img_url(item.get_parent_backdrop_item_id() != "" ? item.get_parent_backdrop_item_id() : item.get_id(), JellyfinClient::BACKDROP);
        BigMovieVignette *vign = _ctn_resume_movie.make_managed<BigMovieVignette>(_jclient->get_http(), url, item);
        vign->set_vsizing(gana::Node::Sizing::SHRINK_CENTER);
        vign->on_click.connect(*this, &Home::on_item_click);
        _ctn_resume_movie.add_child(vign);
    }
    _app->set_focused_node(&_scr_resume);
}

void Home::on_next_up_receive(gana::Request::RCode code)
{
    if (code != gana::Request::OK) {
        gana::Logger::error("%s", _rnext_up->get_error_str().c_str());
        return;
    }
    for (auto &item: _rnext_up->get_items()) {
        std::string url = _jclient->get_img_url(item.get_parent_backdrop_item_id() != "" ? item.get_parent_backdrop_item_id() : item.get_id(), JellyfinClient::BACKDROP);
        BigMovieVignette *vign = _ctn_next_up.make_managed<BigMovieVignette>(_jclient->get_http(), url, item);
        vign->set_vsizing(gana::Node::Sizing::SHRINK_CENTER);
        vign->on_click.connect(*this, &Home::on_item_click);
        _ctn_next_up.add_child(vign);
    }
}

void Home::on_views_receive(gana::Request::RCode code)
{
    if (code != gana::Request::OK) {
        gana::Logger::error("%s", _rviews->get_error_str().c_str());
        return;
    }
    for (auto &item: _rviews->get_items()) {
        gana::Logger::info("View: %s", item.get_name().c_str());
        gana::Label *lbl = make_managed<gana::Label>();
        lbl->set_text("Latest " + item.get_name());
        lbl->set_font_size(40);
        _ctn_main.add_child(lbl);
        LatestView *view = make_managed<LatestView>(*_jclient.get(), item.get_id());
        view->on_item_selected.connect(*this, &Home::on_item_click);
        _ctn_main.add_child(view);
    }
}

void Home::on_item_click(const Item &item)
{
    gana::Logger::info("Item click %s", item.get_name().c_str());
    switch (item.get_type()) {
        case Item::MOVIE:
            _nav.navigate_down<MovieDetail>(_jclient, item);
            break;
        case Item::SERIE:
            _nav.navigate_down<SerieDetail>(_jclient, item);
            break;
        case Item::EPISODE:
            _nav.navigate_down<EpisodeDetail>(_jclient, item);
            break;
        default:
            gana::Logger::error("failed to navigate down. Unknow item type");
    }
}
