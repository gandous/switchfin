
#include <iostream>
#include "Http.hpp"

static bool lib_curl_init = false;

static size_t read_callback(char *buffer, std::size_t size, std::size_t nitems, void *userdata)
{
    Http::Request *req = (Http::Request*)userdata;
    std::size_t end = std::min(size * nitems + req->rindex, req->rdata.size());
    std::size_t i = req->rindex;

    for (std::size_t windex = 0 ; i < end; i++, windex++)
        buffer[windex] = req->rdata[i];
    return (end - req->rdata.size());
}

static size_t write_callback(char *buffer, std::size_t size, std::size_t nitems, void *userdata)
{
    Http::Request *req = (Http::Request*)userdata;
    req->wdata += buffer;
    return (size * nitems);
}

Http::Http(): _multi_handle(nullptr)
{
    if (!lib_curl_init) {
        CURLcode code = curl_global_init(CURL_GLOBAL_NOTHING);
        if (code != 0) {
            std::cerr << "Curl global init failed (code: " << (int)code << ")" << std::endl;
            return;
        }
        lib_curl_init = true;
    }
    _multi_handle = curl_multi_init();
    if (_multi_handle == nullptr) {
        std::cerr << "Failed to init curl" << std::endl;
    }
}

Http::~Http()
{
    std::cout << "Closing all connection" << std::endl;
    if (lib_curl_init) {
        curl_global_cleanup();
        lib_curl_init = false;
    }
    for (auto &pd: _pending_request) {
        curl_multi_remove_handle(_multi_handle, pd.handle);
        curl_easy_cleanup(pd.handle);
    }
    for (auto handle: _handles)
        curl_easy_cleanup(handle);
    if (_multi_handle != nullptr)
        curl_multi_cleanup(_multi_handle);
    std::cout << "All connection closed" << std::endl;
}

int Http::process()
{
    int still_running;
    CURLMcode mc = curl_multi_perform(_multi_handle, &still_running);
    if(!mc && still_running)
        mc = curl_multi_poll(_multi_handle, NULL, 0, 1000, NULL);
    check_response();
    return (still_running);
}

void Http::request(const std::string &url, const std::string &body, Method method, std::function<void(int code, std::string &body)> callback, std::unordered_map<std::string, std::string> headers)
{
    CURL *handle = get_avai_handle();
    _pending_request.push_back({body, 0, "", handle, callback});
    (void)headers;

    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&_pending_request.back());
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(handle, CURLOPT_USERAGENT, "Switchfin");
    switch (method) {
        default:
        case Method::GET:
            curl_easy_setopt(handle, CURLOPT_HTTPGET, 1L);
            break;
        case Method::POST:
            curl_easy_setopt(handle, CURLOPT_POST, 1L);
            curl_easy_setopt(handle, CURLOPT_READDATA, (void*)&_pending_request.back());
            curl_easy_setopt(handle, CURLOPT_READFUNCTION, read_callback);
            break;
    }
    curl_multi_add_handle(_multi_handle, handle);
}

void Http::post(const std::string &url, const std::string &body, callback_func callback, std::unordered_map<std::string, std::string> headers)
{
    request(url, body, Method::POST, callback, headers);
}

void Http::get(const std::string &url, const std::string &body, callback_func callback, std::unordered_map<std::string, std::string> headers)
{
    request(url, body, Method::GET, callback, headers);
}

CURL *Http::get_avai_handle()
{
    if (_handles.size() > 0) {
        CURL *hd = _handles.front();
        _handles.pop_front();
        return (hd);
    } else {
        return (curl_easy_init());
    }
}

void Http::check_response()
{
    CURLMsg *msg;
    do {
        int msgq = 0;
        msg = curl_multi_info_read(_multi_handle, &msgq);
        if (msg && msg->msg == CURLMSG_DONE) {
            on_response(msg);
        }
    } while (msg != nullptr);
}

void Http::on_response(CURLMsg *msg)
{
    for (std::vector<Request>::iterator it = _pending_request.begin(); it != _pending_request.end(); it++) {
        if (it->handle == msg->easy_handle) {
            (it->callback)(msg->data.result, it->wdata);
            curl_multi_remove_handle(_multi_handle, it->handle);
            curl_easy_reset(it->handle);
            _handles.push_front(it->handle);
            _pending_request.erase(it);
            return;
        }
    }
}
