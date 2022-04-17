
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
    _functions.push_back([&obj, func](ARG ...arg){
        (obj.*func)(arg...);
    });
}

template<typename ...ARG>
void Signal<ARG...>::emit(ARG ...arg)
{
    for (auto f: _functions)
        (f)(arg...);
}
