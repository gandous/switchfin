
#include "TextureButton.hpp"

namespace gana {

TextureButton::TextureButton()
{
    add_child(&_img);
    set_color(gana::Color(0, 0, 0, 0));
}

TextureButton::~TextureButton()
{}

void TextureButton::set_image(const std::string &filepath)
{
    _img.set_image(filepath);
}

}