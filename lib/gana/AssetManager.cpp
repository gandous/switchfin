
#include <iostream>
#include "AssetManager.hpp"

namespace gana {

inline std::string get_prefix()
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

std::string AssetManager::get_path(const std::string &path)
{
#if SWITCH
    return ("romfs:/" + path);
#else
    return ("romfs/" + path);
#endif
}

int AssetManager::load_font(const std::string &name, const std::string &filepath)
{
    std::string path = get_prefix() + filepath;
    int fd = nvgCreateFont(_ctx, name.c_str(), path.c_str());

    if (fd < 0) {
        std::cerr << "Failed to load font " << path << std::endl;
    }
    return (fd);
}

int AssetManager::load_image(const std::string &filepath, int flag)
{
    std::string path = get_prefix() + filepath;
    int fd = nvgCreateImage(_ctx, path.c_str(), flag);

    if (fd == FAILED_RCODE) {
        std::cerr << "Failed to load font " << path << std::endl;
    }
    return (fd);
}

}