
#ifndef TEXTUREBUTTON_HPP_
#define TEXTUREBUTTON_HPP_

#include "BaseButton.hpp"
#include "Image.hpp"

namespace gana {

class TextureButton: public BaseButton {
    public:
        TextureButton();
        ~TextureButton();

        void set_image(const std::string &filepath);
    private:
        Image _img;
};

}

#endif /* TEXTUREBUTTON_HPP_ */