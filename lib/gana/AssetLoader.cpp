
#include <iostream>
#include "AssetLoader.hpp"

namespace gana {

int AssetLoader::load_font(NVGcontext *ctx, const std::string &name, const std::string &filepath)
{
#if SWITCH
    std::string path = "romfs:/" + filepath;
#else
    std::string path = "romfs/" + filepath;
#endif
    if (nvgCreateFont(ctx, name.c_str(), path.c_str()) < 0) {
        std::cerr << "Failed to load font " << path << std::endl;
    }
    return (0);
}

}