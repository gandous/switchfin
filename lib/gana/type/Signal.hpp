
#ifndef SIGNAL_HPP_
#define SIGNAL_HPP_

#include <vector>
#include <functional>

namespace gana {

template<typename ...ARG>
class Signal {
    public:
        Signal();
        ~Signal();

        template<typename T>
        void connect(T &obj, void(T::*func)(ARG...));
        void emit(ARG ...arg);
    private:
        std::vector<std::function<void(ARG...)>> _functions;
};

#include "Signal.inl"

}

#endif /* SIGNAL_HPP_ */