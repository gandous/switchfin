
#ifndef ITEMREQUEST_HPP_
#define ITEMREQUEST_HPP_

#include <memory>
#include "network/Request.hpp"
#include "network/item/Item.hpp"

class ItemRequest: public gana::Request {
    public:
        ItemRequest();
        ~ItemRequest();

        const Item &get_item() const;
    protected:
        void parse();
    private:
        std::unique_ptr<Item> _item;
};

#endif /* ITEMREQUEST_HPP_ */