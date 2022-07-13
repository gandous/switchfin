
#ifndef MEDIAVIGNETTE_HPP_
#define MEDIAVIGNETTE_HPP_

#include "gana/ui/BaseButton.hpp"
#include "gana/ui/NetworkImage.hpp"
#include "network/item/Item.hpp"
#include "type/Signal.hpp"

class MediaVignette: public gana::BaseButton {
    public:
        MediaVignette(gana::Http &http, const std::string &url, const Item &item);
        ~MediaVignette();

        int get_outline_corner_radius() const override;
        gana::Signal<const Item&> on_click;
    private:
        void on_item_pressed();
        const Item &_item;
        gana::NetworkImage _img_background;
};

#endif /* MEDIAVIGNETTE_HPP_ */