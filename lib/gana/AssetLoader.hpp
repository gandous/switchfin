
#ifndef ASSETLOADER_HPP_
#define ASSETLOADER_HPP_

#include <string>
#include "nanovg/src/nanovg.h"

namespace gana {

class AssetLoader {
    public:
        ~AssetLoader() = default;

        static int load_font(NVGcontext *ctx, const std::string &name, const std::string &filepath);
    private:
};

}

#endif /* ASSETLOADER_HPP_ */