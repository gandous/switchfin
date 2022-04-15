
#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <string>
#include <vector>
#include <iostream>

namespace gana {

class Logger {
    public:
        ~Logger() = default;

        template<typename ...ARGS>
        static void print(const std::string &format, ARGS ...args);
        static void print(const std::string &format);

    private:
        template<typename T, typename ...ARGS>
        static void parse_arg(std::vector<std::string> &args, T arg, ARGS ...rest);
        template<typename T>
        static void parse_arg(std::vector<std::string> &args, T arg);
};

#include "Logger.inl"

}

#endif /* LOGGER_HPP_ */