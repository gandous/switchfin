
#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <string>
#include "ui/Node.hpp"

namespace gana {

class Image: public Node {
    public:
        Image();
        ~Image();

        enum StretchMode {
            IMAGE,
            KEEP_ASPECT_COVERED,
            KEEP_ASPECT_FIT,
        };

        void draw(NVGcontext *ctx);
        void set_size(const Vector2f &size) override;
        void set_image(const std::string &filepath);
        void set_stretch_mode(StretchMode stretch_mode);
    private:
        void apply_strectch_mode();
        int _image_id;
        std::string _img_path;
        NVGpaint _paint;
        StretchMode _stretch_mode;
};

}

#endif /* IMAGE_HPP_ */