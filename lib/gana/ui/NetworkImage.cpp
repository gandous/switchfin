
#include "App.hpp"
#include "NetworkImage.hpp"

namespace gana {

NetworkImage::NetworkImage()
{}

NetworkImage::~NetworkImage()
{}

void NetworkImage::set_image(Http &http, const std::string &url,  const Http::UrlParams &params)
{
    _http = &http;
    _img_path = url;
    _params = params;
}

void NetworkImage::enter_tree()
{
    if (_http != nullptr && _image_id == AssetManager::FAILED_RCODE) {
        _req = std::make_shared<Request>();
        _http->get(_req, _img_path, {}, _params);
        _req->set_callback(Request::mf_callback(*this, &NetworkImage::on_request_complete));
    }
}

void NetworkImage::on_request_complete(Request::RCode code)
{
    if (code != Request::RCode::OK)
        return;
    _image_id = _app->get_asset_manager().load_image(_img_path, _req->get_body());
    if (_image_id != AssetManager::FAILED_RCODE)
        apply_strectch_mode();
}

}
