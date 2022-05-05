
#ifndef BIGMOVIEVIGNETTE_HPP_
#define BIGMOVIEVIGNETTE_HPP_

#include "gana/ui/RectContainer.hpp"
#include "gana/ui/NetworkImage.hpp"
#include "gana/ui/Label.hpp"
#include "network/item/Item.hpp"

class BigMovieVignette: public gana::RectContainer {
    public:
        BigMovieVignette(gana::Http &http, const std::string &url, const Item &item);
        ~BigMovieVignette();

        int get_outline_corner_radius() const override;
    private:
        gana::NetworkImage _img_background;
        gana::Label _lbl_title;
};

#endif /* BIGMOVIEVIGNETTE_HPP_ */