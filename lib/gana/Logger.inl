
template<typename ...ARGS>
void Logger::print(FILE *fd, const std::string &format, ARGS ...args)
{
    fprintf(fd, format.c_str(), args...);
}

template<typename ...ARGS>
void Logger::error(const std::string &format, ARGS ...args)
{
    print(stderr, "[ERROR]: " + format + "\n", args...);
}

template<typename ...ARGS>
void Logger::warning(const std::string &format, ARGS ...args)
{
    print(stdout, "[WARNING]: " + format + "\n", args...);
}

template<typename ...ARGS>
void Logger::info(const std::string &format, ARGS ...args)
{
    print(stdout, "[INFO]: " + format + "\n", args...);
}