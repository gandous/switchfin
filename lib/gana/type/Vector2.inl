
template<typename T>
inline Vector2<T>::Vector2(): x(0), y(0)
{}


template<typename T>
inline Vector2<T>::Vector2(T x, T y): x(x), y(y)
{}


template<typename T>
inline Vector2<T>::Vector2(const Vector2<T> &vect): x(vect.x), y(vect.y)
{}

template<typename T>
inline Vector2<T>::~Vector2()
{}

template<typename T>
inline Vector2<T> Vector2<T>::normalize()
{
    float length = this->length();
    if (length == 0)
        return (Vector2(0, 0));
    return (Vector2(this->x / length, this->y / length));
}

template<typename T>
inline float Vector2<T>::length()
{
    return (std::sqrt(this->x * this->x + this->y * this->y));
}

template<typename T>
inline float Vector2<T>::distance(const Vector2<T> &point)
{
    return (std::sqrt(std::pow(this->x - point.x, 2) + std::pow(this->y - point.y, 2)));
}

template<typename T>
inline std::string Vector2<T>::to_string() const
{
    std::ostringstream str;
    str << "Vector2(" << x << ", " << y << ")";
    return (str.str());
}

template<typename T>
inline Vector2<T> &Vector2<T>::operator*(T nb)
{
    this->x *= nb;
    this->y *= nb;
    return (*this);
}

template<typename T>
inline Vector2<T> Vector2<T>::operator*(const Vector2<T> &vec) const
{
    Vector2<T> v;
    v.x = this->x * vec.x;
    v.y = this->y * vec.y;
    return (v);
}

template<typename T>
inline Vector2<T> Vector2<T>::operator-(const Vector2<T> &vec) const
{
    Vector2<T> v;
    v.x = this->x - vec.x;
    v.y = this->y - vec.y;
    return (v);
}

template<typename T>
inline Vector2<T> Vector2<T>::operator+(const Vector2<T> &vec) const
{
    Vector2<T> v;
    v.x = this->x + vec.x;
    v.y = this->y + vec.y;
    return (v);
}

template<typename T>
Vector2<T> &Vector2<T>::operator=(const Vector2<T> &vec)
{
    this->x = vec.x;
    this->y = vec.y;
    return (*this);
}
