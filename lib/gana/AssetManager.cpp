
#include <iostream>
#include "AssetManager.hpp"

namespace gana {

inline std::string get_path()
{
#if SWITCH
    return ("romfs:/");
#else
    return ("romfs/");
#endif
}

AssetManager::AssetManager(NVGcontext *ctx): _ctx(ctx)
{}

AssetManager::~AssetManager()
{}

int AssetManager::load_font(const std::string &name, const std::string &filepath)
{
    std::string path = get_path() + filepath;
    int fd = nvgCreateFont(_ctx, name.c_str(), path.c_str());

    if (fd < 0) {
        std::cerr << "Failed to load font " << path << std::endl;
    }
    return (fd);
}

int AssetManager::load_image(const std::string &filepath, int flag)
{
    std::string path = get_path() + filepath;
    int fd = nvgCreateImage(_ctx, path.c_str(), flag);

    if (fd == FAILED_RCODE) {
        std::cerr << "Failed to load font " << path << std::endl;
    }
    return (fd);
}

}