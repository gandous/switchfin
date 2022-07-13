
#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>
#include <vector>
#include "UserData.hpp"
#include "json/json.hpp"
#include "item_type.hpp"

class Item {
    public:
        Item(nlohmann::json &json);
        ~Item();

        enum Type {
            MOVIE,
            SERIE,
            EPISODE,
            COLLECTION_FOLDER,
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
        Tick get_runtime_tick() const;
        int get_prod_year() const;
        int get_index_number() const;
        int get_parent_index_number() const;
        bool get_is_hd() const;
        bool get_is_folder() const;
        const std::string &get_parent_id() const;
        Type get_type() const;
        const std::string &get_parent_backdrop_item_id() const;
        const UserData &get_user_data() const;
        const std::string &get_serie_name() const;
        const std::string &get_season_name() const;
        const std::string &get_serie_id() const;
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
        Tick _runtime_tick;
        int _prod_year;
        int _index_number;
        int _parent_index_number;
        bool _is_hd;
        bool _is_folder;
        std::string _parent_id;
        Type _type;
        std::string _parent_backdrop_item_id;
        UserData _userdata;
        std::string _serie_name;
        std::string _season_name;
        std::string _serie_id;
};

using Items = std::vector<Item>;

#endif /* ITEM_HPP_ */