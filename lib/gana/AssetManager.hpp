
#ifndef AssetManager_HPP_
#define AssetManager_HPP_

#include <string>
#include <unordered_map>
#include <cstring>
#include <vector>
#include "nanovg/src/nanovg.h"

namespace gana {

class AssetManager {
    public:
        static const int FAILED_RCODE = 0;

        AssetManager(NVGcontext *ctx);
        ~AssetManager();

        static std::string get_path(const std::string &path);

        int load_font(const std::string &name, const std::string &filepath);
        int load_image(const std::string &filepath, int flag = 0);
        int load_image(const std::string &name, const std::vector<unsigned char> &data, int flag = 0);
    private:
        NVGcontext *_ctx;
        std::unordered_map<std::string, int> _images;
        std::unordered_map<std::string, std::vector<unsigned char>> _images_data;
};

}

#endif /* AssetManager_HPP_ */