
#include <sstream>
#include "Logger.hpp"
#include "Http.hpp"

namespace gana {

static bool lib_curl_init = false;

static size_t read_callback(char *buffer, std::size_t size, std::size_t nitems, void *userdata)
{
    Request::ReadStruct *req = (Request::ReadStruct*)userdata;
    std::size_t end = std::min(size * nitems + req->index, req->data.size());
    std::size_t i = req->index;
    std::size_t start = req->index;

    for (std::size_t windex = 0 ; i < end; i++, windex++)
        buffer[windex] = req->data[i];
    req->index = end;
    return (end - start);
}

static size_t write_callback(char *buffer, std::size_t size, std::size_t nitems, void *userdata)
{
    Request::WriteStruct *req = (Request::WriteStruct*)userdata;
    std::size_t last_index = req->data.size();
    std::size_t new_size = last_index + (size * nitems);
    req->data.resize(new_size);
    for (std::size_t i = 0; last_index < new_size; last_index++, i++)
        req->data[last_index] = buffer[i];
    return (size * nitems);
}

Http::Http(): _multi_handle(nullptr)
{
    if (!lib_curl_init) {
        CURLcode code = curl_global_init(CURL_GLOBAL_NOTHING);
        if (code != 0) {
            gana::Logger::error("Curl global init failed (code: %d)", code);
            return;
        }
        lib_curl_init = true;
    }
    _multi_handle = curl_multi_init();
    if (_multi_handle == nullptr) {
        gana::Logger::error("Failed to init curl");
    }
}

Http::~Http()
{
    gana::Logger::info("Closing all connection");
    if (lib_curl_init) {
        curl_global_cleanup();
        lib_curl_init = false;
    }
    for (auto &pd: _pending_request) {
        if (!pd.expired()) {
            std::shared_ptr<Request> req = pd.lock();
            curl_multi_remove_handle(_multi_handle, req->_handle);
            curl_easy_cleanup(req->_handle);
        }
    }
    for (auto handle: _handles)
        curl_easy_cleanup(handle);
    if (_multi_handle != nullptr)
        curl_multi_cleanup(_multi_handle);
    gana::Logger::info("All connection closed");
}

int Http::process()
{
    int still_running;
    CURLMcode mc = curl_multi_perform(_multi_handle, &still_running);
    if(!mc && still_running)
        mc = curl_multi_poll(_multi_handle, NULL, 0, 0, NULL);
    check_response();
    return (still_running);
}

void Http::request(std::shared_ptr<Request> req, const std::string &url, const std::string &body, Method method, const Headers &headers)
{
    CURL *handle = get_avai_handle();
    _pending_request.push_back(std::weak_ptr<Request>(req));

    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&req->_wdata);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(handle, CURLOPT_USERAGENT, "Switchfin");
    if (headers.size() > 0) {
        for (auto header: headers) {
            std::string hs = header.first + ": " + header.second;
            req->_headers = curl_slist_append(req->_headers, hs.c_str());
        }
        curl_easy_setopt(handle, CURLOPT_HTTPHEADER, req->_headers);
    }
    switch (method) {
        default:
        case Method::GET:
            curl_easy_setopt(handle, CURLOPT_HTTPGET, 1L);
            break;
        case Method::POST:
            req->_rdata.data = body;
            req->_rdata.index = 0;
            curl_easy_setopt(handle, CURLOPT_POST, 1L);
            curl_easy_setopt(handle, CURLOPT_READDATA, (void*)&req->_rdata);
            curl_easy_setopt(handle, CURLOPT_READFUNCTION, read_callback);
            break;
    }
    req->_handle = handle;
    req->_parent = this;
    curl_multi_add_handle(_multi_handle, handle);
#if DEBUG_HTTP
    gana::Logger::info("Request %s %s", Method::POST ? "POST" : "GET", url.c_str());
#endif
}

void Http::post(std::shared_ptr<Request> req, const std::string &url, const std::string &body, const Headers &headers, const UrlParams &params)
{
    if (params.size() != 0)
        request(req, format_url_params(url, params), body, Method::POST, headers);
    else
        request(req, url, body, Method::POST, headers);
}

void Http::get(std::shared_ptr<Request> req, const std::string &url, const Headers &headers, const UrlParams &params)
{
    if (params.size() != 0)
        request(req, format_url_params(url, params), "", Method::GET, headers);
    else
        request(req, url, "", Method::GET, headers);
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
    for (std::vector<std::weak_ptr<Request>>::iterator it = _pending_request.begin(); it != _pending_request.end(); it++) {
        if (it->expired())
            return;
        std::shared_ptr<Request> req = it->lock();
        if (req->_handle == msg->easy_handle) {
            curl_easy_getinfo(req->_handle, CURLINFO_RESPONSE_CODE, &req->_http_code);
#if DEBUG_HTTP
            gana::Logger::info("Response (code: %d)", req->_http_code);
#endif
            curl_multi_remove_handle(_multi_handle, req->_handle);
            curl_easy_reset(req->_handle);
            _handles.push_front(req->_handle);
            _pending_request.erase(it);
            req->_handle = nullptr;
            req->_parent = nullptr;
            req->_completed = true;
            req->_curl_code = msg->data.result;
            if (req->_headers != nullptr) {
                curl_slist_free_all(req->_headers);
                req->_headers = nullptr;
            }
            req->parse();
            return;
        }
    }
}

std::string Http::format_url_params(const std::string &url, const UrlParams &params)
{
    std::ostringstream param;
    bool first = true;

    param << url << "?";
    for (UrlParams::const_iterator p = params.begin(); p != params.end(); p++) {
        if (first)
            first = false;
        else
            param << "&";
        param << p->first << "=" << p->second;
    }
    return (param.str());
}

}
