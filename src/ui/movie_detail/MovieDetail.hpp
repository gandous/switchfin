
#ifndef MOVIE_DETAIL_HPP_
#define MOVIE_DETAIL_HPP_

#include "ui/ColorRect.hpp"
#include "ui/NavigationManager.hpp"
#include "network/JellyfinClient.hpp"

class MovieDetail: public gana::ColorRect {
    public:
        MovieDetail(gana::NavigationManager &nav, std::shared_ptr<JellyfinClient> client, const Item &item);
        ~MovieDetail();

    private:
};

#endif /* MOVIE_DETAIL_HPP_ */