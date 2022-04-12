
template<typename T>
inline Rect<T>::Rect(): x(0), y(0), w(0), h(0)
{}

template<typename T>
inline Rect<T>::Rect(T x, T y, T w, T h): x(x), y(y), w(w), h(h)
{}

template<typename T>
inline Rect<T>::Rect(Vector2<T> position, Vector2<T> size): x(position.x), y(position.y), w(size.x), h(size.y)
{}

template<typename T>
inline Rect<T>::~Rect()
{}