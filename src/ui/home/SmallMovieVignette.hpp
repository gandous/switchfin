
#ifndef SMALLMOVIEVIGNETTE_HPP_
#define SMALLMOVIEVIGNETTE_HPP_

#include <string>
#include "gana/ui/RectContainer.hpp"
#include "gana/ui/NetworkImage.hpp"
#include "gana/ui/Label.hpp"
#include "network/item/Item.hpp"

class SmallMovieVignette: public gana::RectContainer {
    public:
        SmallMovieVignette(gana::Http &http, const std::string &url, const Item &item);
        ~SmallMovieVignette();

    private:
        gana::NetworkImage _img_background;
};

#endif /* SMALLMOVIEVIGNETTE_HPP_ */