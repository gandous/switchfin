
#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>
#include "json/json.hpp"

class Item {
    public:
        Item(nlohmann::json &json);
        ~Item();

        const std::string &get_name() const;
        const std::string &get_id() const;
    private:
        std::string _name;
        std::string _id;
};

#endif /* ITEM_HPP_ */