
#ifndef NETWORKIMAGE_HPP_
#define NETWORKIMAGE_HPP_

#include <memory>
#include "network/Http.hpp"
#include "network/Request.hpp"
#include "Image.hpp"

namespace gana {

class NetworkImage: public Image {
    public:
        NetworkImage();
        ~NetworkImage();

        void set_image(Http &http, const std::string &url);
    protected:
        void enter_tree();
    private:
        void on_request_complete(Request::RCode code, Request &req);
        Http *_http;
        std::shared_ptr<Request> _req;
};

}

#endif /* NETWORKIMAGE_HPP_ */