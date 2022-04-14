
template<typename ...ARGS>
void Logger::print(const std::string &format, ARGS ...args)
{
    std::vector<std::string> parse;
    std::size_t arg_index = 0;
    std::string out = format;

    parse_arg(parse, args...);
    for (std::size_t i = 0; format[i] != '\0'; i++) {
        if (out[i] == '$') {
            out.replace(i, (std::size_t)1, parse[arg_index]);
            arg_index++;
        }
    }
    std::cout << out << std::endl;
}

template<typename T, typename ...ARGS>
void Logger::parse_arg(std::vector<std::string> &args, T arg, ARGS ...rest)
{
    using namespace std;
    args.push_back(to_string(arg));
    parse_arg(args, rest...);
}

template<typename T>
void Logger::parse_arg(std::vector<std::string> &args, T arg)
{
    using namespace std;
    args.push_back(to_string(arg));
}