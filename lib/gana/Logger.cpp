
#include <iostream>
#include "Logger.hpp"

namespace gana {

void Logger::print(const std::string &format)
{
    std::cout << format << std::endl;
}

}