
template<typename ...ARG>
Signal<ARG...>::Signal()
{}

template<typename ...ARG>
Signal<ARG...>::~Signal()
{}

template<typename ...ARG>
template<typename T>
void Signal<ARG...>::connect(T &obj, void(T::*func)(ARG...))
{
    _functions.push_back(std::make_pair((void*)&obj, [&obj, func](ARG ...arg){
        (obj.*func)(arg...);
    }));
}

template<typename ...ARG>
void Signal<ARG...>::emit(ARG ...arg)
{
    for (auto f: _functions)
        (f.second)(arg...);
}

template<typename ...ARG>
template<typename T>
void Signal<ARG...>::disconnect(T &obj)
{
    for (std::size_t i = 0; i < _functions.size(); i++) {
        if (_functions[i].first == (void*)&obj) {
            _functions.erase(_functions.begin() + i);
        }
    }
}