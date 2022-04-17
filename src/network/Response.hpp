
#ifndef RESPONSE_HPP_
#define RESPONSE_HPP_

#include <string>

class Response {
    public:
        Response(int code, const std::string &data);
        ~Response();

        int get_error() const;
        const std::string &get_error_str() const;
    protected:
        int _code;
        std::string _data;
    private:
};

#endif /* RESPONSE_HPP_ */