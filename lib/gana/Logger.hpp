
#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>

namespace gana {

class Logger {
    public:
        ~Logger() = default;

        template<typename ...ARGS>
        static void print(FILE *fd, const std::string &format, ARGS ...args);
        template<typename ...ARGS>
        static void error(const std::string &format, ARGS ...args);
        template<typename ...ARGS>
        static void warning(const std::string &format, ARGS ...args);
        template<typename ...ARGS>
        static void info(const std::string &format, ARGS ...args);

    private:
};

#include "Logger.inl"

}

#endif /* LOGGER_HPP_ */