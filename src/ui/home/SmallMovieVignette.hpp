
#ifndef SMALLMOVIEVIGNETTE_HPP_
#define SMALLMOVIEVIGNETTE_HPP_

#include <string>
#include "gana/type/Signal.hpp"
#include "gana/ui/BaseButton.hpp"
#include "gana/ui/NetworkImage.hpp"
#include "gana/ui/Label.hpp"
#include "network/item/Item.hpp"

class SmallMovieVignette: public gana::BaseButton {
    public:
        SmallMovieVignette(gana::Http &http, const std::string &url, const Item &item);
        ~SmallMovieVignette();

        gana::Signal<const Item&> on_click;
    private:
        void on_item_pressed();
        const Item &_item;
        gana::NetworkImage _img_background;
};

#endif /* SMALLMOVIEVIGNETTE_HPP_ */