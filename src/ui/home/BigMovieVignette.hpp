
#ifndef BIGMOVIEVIGNETTE_HPP_
#define BIGMOVIEVIGNETTE_HPP_

#include "gana/ui/RectContainer.hpp"
#include "gana/ui/NetworkImage.hpp"
#include "gana/ui/Label.hpp"
#include "gana/ui/GradientColorRect.hpp"
#include "network/item/Item.hpp"
#include "type/Signal.hpp"

class BigMovieVignette: public gana::RectContainer {
    public:
        BigMovieVignette(gana::Http &http, const std::string &url, const Item &item);
        ~BigMovieVignette();

        int get_outline_corner_radius() const override;
        void process_event(gana::Event &evt) override;
        gana::Signal<const Item&> on_click;
    private:
        const Item &_item;
        gana::NetworkImage _img_background;
        gana::Label _lbl_title;
        gana::Node _node;
        gana::GradientColorRect _gdt_background;
};

#endif /* BIGMOVIEVIGNETTE_HPP_ */