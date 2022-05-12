
#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>
#include <vector>
#include "UserData.hpp"
#include "json/json.hpp"

class Item {
    public:
        Item(nlohmann::json &json);
        ~Item();

        enum Type {
            MOVIE,
            SERIE,
            UNKNOW,
        };

        const std::string &get_name() const;
        const std::string &get_original_title() const;
        const std::string &get_server_id() const;
        const std::string &get_id() const;
        const std::string &get_etag() const;
        const std::string &get_path() const;
        const std::string &get_official_rating() const;
        const std::string &get_overview() const;
        const std::vector<std::string> &get_taglines() const;
        const std::vector<std::string> &get_genres() const;
        float get_community_rating() const;
        int get_runtime_tick() const;
        int get_prod_year() const;
        bool get_is_hd() const;
        bool get_is_folder() const;
        const std::string &get_parent_id() const;
        Type get_type() const;
        const UserData &get_user_data() const;
    private:
        static Type parse_type(const std::string &type);
        std::string _name;
        std::string _original_title;
        std::string _server_id;
        std::string _id;
        std::string _etag;
        std::string _path;
        std::string _official_rating;
        std::string _overview;
        std::vector<std::string> _taglines;
        std::vector<std::string> _genres;
        float _community_rating;
        int _runtime_tick;
        int _prod_year;
        bool _is_hd;
        bool _is_folder;
        std::string _parent_id;
        Type _type;
        UserData _userdata;
};

using Items = std::vector<Item>;

#endif /* ITEM_HPP_ */