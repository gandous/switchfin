
#ifndef SEASONVIGNETTE_HPP_
#define SEASONVIGNETTE_HPP_

#include "gana/ui/NetworkImage.hpp"
#include "gana/ui/Label.hpp"
#include "gana/ui/box_container/VBoxContainer.hpp"
#include "gana/ui/RectContainer.hpp"
#include "network/item/Item.hpp"
#include "network/JellyfinClient.hpp"

class SeasonVignette: public gana::RectContainer {
    public:
        SeasonVignette(JellyfinClient &client, const Item &item);
        ~SeasonVignette();

    protected:
        int get_outline_corner_radius() const;
    private:
        gana::VBoxContainer _ctn;
        gana::NetworkImage _img;
        gana::Label _lbl;
};

#endif /* SEASONVIGNETTE_HPP_ */