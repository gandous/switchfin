
#ifndef ITEMS_HPP_
#define ITEMS_HPP_

#include "network/Request.hpp"
#include "network/item/Item.hpp"

class ItemsRequest: public gana::Request {
    public:
        ItemsRequest();
        ~ItemsRequest();

        const Items &get_items() const;
    protected:
        void parse();
    private:
        Items _items;
};

#endif /* ITEMS_HPP_ */