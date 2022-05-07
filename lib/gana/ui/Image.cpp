
#include "Image.hpp"
#include "theme/color.hpp"
#include "App.hpp"

namespace gana {

Image::Image(): _image_id(AssetManager::FAILED_RCODE), _corner_radius(0), _stretch_mode(IMAGE)
{}

Image::~Image()
{}

void Image::draw(NVGcontext *ctx)
{
    nvgSave(ctx);
    nvgBeginPath(ctx);
    if (_image_id == AssetManager::FAILED_RCODE) {
        nvgRoundedRect(ctx, get_draw_positon().x, get_draw_positon().y, get_draw_size().x, get_draw_size().y, _corner_radius);
        nvgFillColor(ctx, theme::IMG_FAILED_BG_COLOR.nvg_color());
        nvgFill(ctx);
    } else {
        nvgRoundedRect(ctx, get_draw_positon().x, get_draw_positon().y, get_draw_size().x, get_draw_size().y, _corner_radius);
        nvgTranslate(ctx, get_draw_positon().x, get_draw_positon().y);
        nvgFillPaint(ctx, _paint);
        nvgFill(ctx);
    }
    nvgRestore(ctx);
}

void Image::set_size(const Vector2f &size)
{
    Node::set_size(size);
    if (_image_id != AssetManager::FAILED_RCODE)
        apply_strectch_mode();
}

void Image::set_image(const std::string &filepath)
{
    if (_app == nullptr) {
        _img_path = filepath;
        return;
    }
    _image_id = _app->get_asset_manager().load_image(filepath);
    if (_image_id == AssetManager::FAILED_RCODE)
        return;
    apply_strectch_mode();
}

void Image::set_stretch_mode(StretchMode stretch_mode)
{
    _stretch_mode = stretch_mode;
    if (_image_id != AssetManager::FAILED_RCODE)
        apply_strectch_mode();
}

void Image::set_corner_radius(int radius)
{
    _corner_radius = radius;
}

void Image::enter_tree()
{
    if (_img_path != "") {
        set_image(_img_path);
        _img_path = "";
        if (_image_id == AssetManager::FAILED_RCODE)
            return;
    }
}

void Image::apply_strectch_mode()
{
    int w;
    int h;
    nvgImageSize(_app->get_nvg_context(), _image_id, &w, &h);
    switch (_stretch_mode) {
        case IMAGE:
            set_min_size(Vector2f(w, h));
            _paint = nvgImagePattern(_app->get_nvg_context(), 0, 0, w, h, 0, _image_id, 1);
            break;
        // case KEEP_CENTER: {
        //     float x = get_size().x / 2.0 - w / 2.0;
        //     float y = get_size().y / 2.0 - h / 2.0;
        //     set_min_size(Vector2f(0, 0));
        //     _paint = nvgImagePattern(_app->get_nvg_context(), x, y, get_size().x, get_size().y, 0, _image_id, 1);
        //     } break;
        case KEEP_ASPECT_COVERED: {
            float ratio = std::max(get_size().x / w, get_size().y / h);
            set_min_size(Vector2f(0, 0));
            _paint = nvgImagePattern(_app->get_nvg_context(), get_size().x / 2 - (w * ratio) / 2, get_size().y / 2 - (h * ratio) / 2, w * ratio, h * ratio, 0, _image_id, 1);
            } break;
        case KEEP_ASPECT_FIT: {
            float ratio = std::min(get_size().x / w, get_size().y / h);
            set_min_size(Vector2f(0, 0));
            _paint = nvgImagePattern(_app->get_nvg_context(), 0, 0, w * ratio, h * ratio, 0, _image_id, 1);
            } break;
    }
}

}
