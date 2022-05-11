
#ifndef GENRE_HPP_
#define GENRE_HPP_

#include "gana/ui/BGRectContainer.hpp"
#include "gana/ui/Label.hpp"

class Genre: public gana::BGRectContainer {
    public:
        Genre(const std::string &name);
        ~Genre();

    private:
        gana::Label _lbl_name;
};

#endif /* GENRE_HPP_ */