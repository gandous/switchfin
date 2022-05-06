
#ifndef ITEMLISTREQUEST_HPP_
#define ITEMLISTREQUEST_HPP_

#include "network/Request.hpp"
#include "Item.hpp"

// Some api route return directly a list of item some return an object container an item row
// This class is used to parse the route returning directly a list
class ItemListRequest: public gana::Request {
    public:
        ItemListRequest();
        ~ItemListRequest();

        const Items &get_items() const;
    protected:
        void parse();
    private:
        Items _items;
};

#endif /* ITEMLISTREQUEST_HPP_ */