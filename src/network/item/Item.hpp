
#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>
#include "json/json.hpp"

class Item {
    public:
        Item(nlohmann::json &json);
        ~Item();

        const std::string &get_name() const;
    private:
        std::string _name;
};

#endif /* ITEM_HPP_ */