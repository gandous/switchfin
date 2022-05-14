
#ifndef SIGNAL_HPP_
#define SIGNAL_HPP_

#include <vector>
#include <functional>
#include <utility>

namespace gana {

template<typename ...ARG>
class Signal {
    public:
        Signal();
        ~Signal();

        template<typename T>
        void connect(T &obj, void(T::*func)(ARG...));
        void emit(ARG ...arg);
        template<typename T>
        void disconnect(T &obj);
    private:
        std::vector<std::pair<void*, std::function<void(ARG...)>>> _functions;
};

#include "Signal.inl"

}

#endif /* SIGNAL_HPP_ */