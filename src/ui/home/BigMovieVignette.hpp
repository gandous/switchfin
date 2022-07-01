
#ifndef BIGMOVIEVIGNETTE_HPP_
#define BIGMOVIEVIGNETTE_HPP_

#include "gana/ui/BaseButton.hpp"
#include "gana/ui/NetworkImage.hpp"
#include "gana/ui/Label.hpp"
#include "gana/ui/GradientColorRect.hpp"
#include "network/item/Item.hpp"
#include "ProgressBar.hpp"
#include "type/Signal.hpp"

class BigMovieVignette: public gana::BaseButton {
    public:
        BigMovieVignette(gana::Http &http, const std::string &url, const Item &item);
        ~BigMovieVignette();

        int get_outline_corner_radius() const override;
        gana::Signal<const Item&> on_click;
    private:
        void on_item_pressed();
        const Item &_item;
        gana::NetworkImage _img_background;
        gana::Label _lbl_title;
        gana::Node _node;
        gana::GradientColorRect _gdt_background;
        ProgressBar _pgsb_time_watch;
};

#endif /* BIGMOVIEVIGNETTE_HPP_ */